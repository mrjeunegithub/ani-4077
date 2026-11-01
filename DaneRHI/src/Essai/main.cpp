// =============================================================================
// Chapitre 8 : comparaison des maillages avec et sans index.
// =============================================================================
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKWindow/Core/NkSurface.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkWindowEvent.h"

#include "NKLogger/NkLog.h"
#include "NKPlatform/NkEnv.h"
#include "NKTime/NkChrono.h"
#include "MonRhi/MonRhi.h"
#include "MonRhi/Contexte.h"
#include "MonRhi/Maillage.h"
#include "MonRhi/Nuanceur.h"
#include "MonRhi/Gl.h"
// Retiré l'include EtatGl.h ajouté pour l'exercice précédent.

#include <cstddef> // Pour std::size_t et les calculs d'octets.
#include <cstdlib>

using namespace nkentseu;

namespace {

	const float kPetroleR = 0.05f;
	const float kPetroleV = 0.25f;
	const float kPetroleB = 0.28f;

	// Nuanceur de sommets conservé depuis le chapitre 6.
	const char *kSommets = R"(
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aCouleur;

out vec3 vCouleur;

void main() {
    vCouleur = aCouleur;
    gl_Position = vec4(aPosition, 1.0);
}
)";

	// Nuanceur de fragments conservé depuis le chapitre 6.
	const char *kFragments = R"(
in vec3 vCouleur;

out vec4 oCouleur;

void main() {
    oCouleur = vec4(vCouleur, 1.0);
}
)";

	const monrhi::Sommet kCarreCoins[4] = {
    { -0.20f, -0.20f, 0.0f, 0.96f, 0.62f, 0.14f }, // 0 : bas gauche
    {  0.20f, -0.20f, 0.0f, 0.20f, 0.75f, 0.70f }, // 1 : bas droite
    {  0.20f,  0.20f, 0.0f, 0.90f, 0.30f, 0.35f }, // 2 : haut droite
    { -0.20f,  0.20f, 0.0f, 0.95f, 0.95f, 0.95f }, // 3 : haut gauche
};

// Pour le premier essai :
const unsigned short kCarreIndex[6] = { 0, 1, 2, 0, 2, 3 };
const char *kOrdreTexte = "{0,1,2, 0,2,3}";

//[À essayer ensuite] :
// const unsigned short kCarreIndex[6] = { 0, 1, 2, 2, 3, 0 };
// const char *kOrdreTexte = "{0,1,2, 2,3,0}";

//[Troisième essai] Puis par :
//const unsigned short kCarreIndex[6] = { 0, 2, 1, 0, 3, 2 };
//const char *kOrdreTexte = "{0,2,1, 0,3,2}";

//Change aussi cette valeur entre les deux lancements de chaque ordre.
constexpr bool kActiverTri = true;
}
int nkmain(const NkEntryState &state) {
	(void)state;

	NkInitialise();
	NkChrono::BeginPreciseTiming();

	NkWindowConfig cfg;
	cfg.title = "Etape 08 "; 
	cfg.width = 1280;
	cfg.height = 720;
	cfg.centered = true;

	NkWindow fenetre(cfg);
	if (!fenetre.IsValid()) {
		logger.Error("la fenetre ne s'est pas ouverte");
		NkClose();
		return 1;
	}

	const NkSurfaceDesc surface = fenetre.GetSurfaceDesc();
	logger.Infof("%s", monrhi::DecrireSurface(surface).CStr());

	monrhi::Contexte contexte;
	constexpr bool kRetirerVerificationGlad = true; // false : premier lancement, glad vérifie
	if (!contexte.Creer(surface)) {
		logger.Error("contexte impossible : on s'arrete ici.");
		NkClose();
		return 1;
	}
	if (kRetirerVerificationGlad)
    		gladUninstallGLDebug();
	logger.Infof("contexte : %s", contexte.Decrire().CStr());

	monrhi::Nuanceur nuanceur;
	if (!nuanceur.Compiler(kSommets, kFragments)) {
		logger.Errorf("NUANCEUR REFUSE :\n%s", nuanceur.Erreur().CStr());
		contexte.Detruire();
		NkClose();
		return 1;
	}

	monrhi::Maillage carre;
	if (!carre.CreerIndexe(kCarreCoins, 4, kCarreIndex, 6)) {
		logger.Error("creation du carre indexe impossible");
		carre.Detruire();
		nuanceur.Detruire();
		contexte.Detruire();
		NkClose();
		return 1;
}
	
	const char *limite = nkentseu::env::GetEnvVar("MONRHI_IMAGES");
	const unsigned long long maxImages =
		limite != nullptr ? std::strtoull(limite, nullptr, 10) : 0;

	unsigned long long images = 0;
	bool tourne = true;

	if (kActiverTri)
    glEnable(GL_CULL_FACE);
	else
    glDisable(GL_CULL_FACE);

	while (tourne && fenetre.IsOpen()) {
		NkEvent *ev = nullptr;
		while (NkEvents().PollEvent(ev)) {
			if (ev->As<NkWindowCloseEvent>() != nullptr)
				tourne = false;

			if (ev->As<NkWindowSurfaceDestroyedEvent>() != nullptr ||
				ev->As<NkWindowHiddenEvent>() != nullptr)
				contexte.DetacherSurface();

			if (ev->As<NkWindowSurfaceCreatedEvent>() != nullptr ||
				ev->As<NkWindowShownEvent>() != nullptr)
				contexte.RattacherSurface(fenetre.GetSurfaceDesc());
		}

		if (!tourne)
			break;

		if (!contexte.PeutDessiner()) {
			NkChrono::Sleep((int64)16);
			continue;
		}

		const auto taille = fenetre.GetSize();
		glViewport(0, 0, (GLsizei)taille.x, (GLsizei)taille.y);
		glClearColor(kPetroleR, kPetroleV, kPetroleB, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		nuanceur.Activer();

		// Dessine les deux versions du carré et de la maison.
		// Les géométries partagent leurs coordonnées et se superposent.
		nuanceur.Activer();

		while (glGetError() != GL_NO_ERROR) {}

		carre.Dessiner();

		const GLenum erreur = glGetError();

		if (images == 2) { // images commence à zéro : 2 correspond à la 3e image
			unsigned char px[4]{};
			glReadPixels(640, 360, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

			logger.Infof("%s : glGetError = 0x%04X, centre (%u, %u, %u)",
						kRetirerVerificationGlad ? "sans glad" : "avec glad",
						static_cast<unsigned int>(erreur),
						static_cast<unsigned int>(px[0]),
						static_cast<unsigned int>(px[1]),
						static_cast<unsigned int>(px[2]));
		}

		contexte.Echanger();
		NkChrono::YieldThread();

		++images;
		if (maxImages != 0 && images >= maxImages)
			break;
	}

	logger.Infof("%llu images, fermeture propre", images);

	// Les quatre maillages sont détruits avant le contexte OpenGL.
	carre.Detruire();
	nuanceur.Detruire();
	contexte.Detruire();

	NkChrono::EndPreciseTiming();
	NkClose();
	return 0;
}