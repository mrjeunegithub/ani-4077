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
#include <vector>
#include <initializer_list>

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

	struct DonneesGrille {
		std::vector<monrhi::Sommet> sommets;
		std::vector<unsigned int> index32;
		std::vector<unsigned short> index16;
		std::vector<monrhi::Sommet> sansIndex;
	};

	DonneesGrille FabriquerGrille(unsigned int n) {
		DonneesGrille g;

		if (n < 2)
			return g;

		g.sommets.reserve(static_cast<std::size_t>(n) * n);

		// Sommets répartis sur le carré [-0.9, 0.9].
		for (unsigned int ligne = 0; ligne < n; ++ligne) {
			const float y = -0.9f + 1.8f * ligne / (n - 1);

			// Une couleur franche par rangée, alternée une rangée sur deux.
			const bool rangeeClaire = (ligne % 2) == 0;
			const float r = rangeeClaire ? 1.0f : 0.05f;
			const float v = rangeeClaire ? 0.9f : 0.15f;
			const float b = rangeeClaire ? 0.1f : 0.9f;

			for (unsigned int colonne = 0; colonne < n; ++colonne) {
				const float x = -0.9f + 1.8f * colonne / (n - 1);
				g.sommets.push_back({x, y, 0.0f, r, v, b});
			}
		}

		// Chaque case est formée de deux triangles.
		for (unsigned int ligne = 0; ligne + 1 < n; ++ligne) {
			for (unsigned int colonne = 0; colonne + 1 < n; ++colonne) {
				const unsigned int v00 = ligne * n + colonne;
				const unsigned int v10 = v00 + 1;
				const unsigned int v01 = v00 + n;
				const unsigned int v11 = v01 + 1;

				// Triangles : v00-v10-v11 et v00-v11-v01.
				const unsigned int indices[] = {
					v00, v10, v11,
					v00, v11, v01
				};

				for (unsigned int i : indices) {
					g.index32.push_back(i);

					// Pour l'essai 16 bits de N=265, la conversion tronque
					// volontairement les valeurs qui dépassent 65 535.
					g.index16.push_back(static_cast<unsigned short>(i));

					// La version sans index recopie le sommet référencé.
					g.sansIndex.push_back(g.sommets[i]);
				}
			}
		}

		return g;
	}
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

	constexpr bool kIndex32PourCapture = true; // false : capture 2 octets ; true : capture 4 octets

	monrhi::Contexte contexte;
	constexpr bool kRetirerVerificationGlad = false; // false : premier lancement, glad vérifie

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

	for (unsigned int n : {2u, 10u, 100u}) {
		DonneesGrille g = FabriquerGrille(n);

		monrhi::Maillage maillageSans;
		monrhi::Maillage maillageAvec;

		if (!maillageSans.Creer(g.sansIndex.data(),
								static_cast<int>(g.sansIndex.size()))) {
			logger.Error("creation de la grille sans index impossible");
			return 1;
		}

		if (!maillageAvec.CreerIndexe(g.sommets.data(),
									static_cast<int>(g.sommets.size()),
									g.index16.data(),
									static_cast<int>(g.index16.size()))) {
			maillageSans.Detruire();
			logger.Error("creation de la grille indexee impossible");
			return 1;
		}

		const std::size_t octetsSans = g.sansIndex.size() * sizeof(monrhi::Sommet);
		const std::size_t octetsAvec =
			g.sommets.size() * sizeof(monrhi::Sommet) +
			g.index16.size() * sizeof(unsigned short);
		const double rapport = static_cast<double>(octetsSans) / octetsAvec;

		logger.Infof("N = %u : sans index %zu octets, avec index %zu octets, rapport %.2f",
					n, octetsSans, octetsAvec, rapport);

		maillageAvec.Detruire();
		maillageSans.Detruire();
	}

	DonneesGrille grande = FabriquerGrille(265);

	monrhi::Maillage grilleGrande;

	if (kIndex32PourCapture) {
		if (!grilleGrande.CreerIndexe32(
				grande.sommets.data(),
				static_cast<int>(grande.sommets.size()),
				grande.index32.data(),
				static_cast<int>(grande.index32.size()))) {
			logger.Error("creation de la grande grille 32 bits impossible");
			return 1;
		}

		const std::size_t octets =
			grande.sommets.size() * sizeof(monrhi::Sommet) +
			grande.index32.size() * sizeof(unsigned int);

		logger.Infof("grille 265 : 70225 sommets, index sur 4 octets, %zu octets",
					octets);
	} else {
		if (!grilleGrande.CreerIndexe(
				grande.sommets.data(),
				static_cast<int>(grande.sommets.size()),
				grande.index16.data(),
				static_cast<int>(grande.index16.size()))) {
			logger.Error("creation de la grande grille 16 bits impossible");
			return 1;
		}

		const std::size_t octets =
			grande.sommets.size() * sizeof(monrhi::Sommet) +
			grande.index16.size() * sizeof(unsigned short);

		logger.Infof("grille 265 : 70225 sommets, index sur 2 octets, %zu octets",
					octets);
	}
	
	const char *limite = nkentseu::env::GetEnvVar("MONRHI_IMAGES");
	const unsigned long long maxImages =
		limite != nullptr ? std::strtoull(limite, nullptr, 10) : 0;

	unsigned long long images = 0;
	bool tourne = true;


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

		while (glGetError() != GL_NO_ERROR) {}

		
		grilleGrande.Dessiner();

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
	grilleGrande.Detruire();
	nuanceur.Detruire();
	contexte.Detruire();

	NkChrono::EndPreciseTiming();
	NkClose();
	return 0;
}