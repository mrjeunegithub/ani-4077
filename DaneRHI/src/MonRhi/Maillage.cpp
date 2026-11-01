// =============================================================================
//  Étape 05 — le tampon, la recette, et l'ordre qui ne se discute pas.
// =============================================================================
#include "MonRhi/Maillage.h"
#include "MonRhi/Gl.h"

#include <cstddef>

namespace monrhi {

	Maillage::~Maillage() {
		Detruire();
	}

	bool Maillage::Creer(const Sommet *sommets, int nombre) {
		Detruire();
		if (sommets == nullptr || nombre <= 0)
			return false;

		glGenVertexArrays(1, &mVao);
		if (mVao == 0)
			return false;
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		if (mVbo == 0)
			return false;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);

		glBufferData(GL_ARRAY_BUFFER,
					 (GLsizeiptr)(sizeof(Sommet) * (size_t)nombre),
					 sommets, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
							  (GLsizei)sizeof(Sommet),
							  (const void *)offsetof(Sommet, x));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							  (GLsizei)sizeof(Sommet),
							  (const void *)offsetof(Sommet, r));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mNombre = nombre;
		return true;
	}

	// Crée un VBO pour les sommets et un EBO pour leurs index.
	bool Maillage::CreerIndexe(const Sommet *sommets, int nombreSommets,
							   const unsigned short *index, int nombreIndex) {
		Detruire();

		if (sommets == nullptr || nombreSommets <= 0 ||
			index == nullptr || nombreIndex <= 0)
			return false;

		// Vérifie que chaque index désigne un sommet existant.
		for (int i = 0; i < nombreIndex; ++i) {
			if (index[i] >= nombreSommets)
				return false;
		}

		// Le VAO doit être lié avant le VBO et les attributs.
		glGenVertexArrays(1, &mVao);
		if (mVao == 0)
			return false;
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		if (mVbo == 0)
			return false;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);

		glBufferData(GL_ARRAY_BUFFER,
					 (GLsizeiptr)(sizeof(Sommet) * (size_t)nombreSommets),
					 sommets, GL_STATIC_DRAW);

		// Décrit la position, comme dans Creer().
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
							  (GLsizei)sizeof(Sommet),
							  (const void *)offsetof(Sommet, x));
		glEnableVertexAttribArray(0);

		// Décrit la couleur, comme dans Creer().
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							  (GLsizei)sizeof(Sommet),
							  (const void *)offsetof(Sommet, r));
		glEnableVertexAttribArray(1);

		// Le lien EBO-VAO est mémorisé par le VAO courant.
		glGenBuffers(1, &mEbo);
		if (mEbo == 0)
			return false;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 (GLsizeiptr)(sizeof(unsigned short) * (size_t)nombreIndex),
					 index, GL_STATIC_DRAW);

		// Délier le VAO en premier conserve son association à l'EBO.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// En mode indexé, mNombre compte les index à dessiner.
		mNombre = nombreIndex;
		mIndex32 = false;
		return true;
	}

	bool Maillage::CreerIndexe32(const Sommet *sommets, int nombreSommets,
								const unsigned int *index, int nombreIndex) {
		Detruire();

		if (sommets == nullptr || nombreSommets <= 0 ||
			index == nullptr || nombreIndex <= 0)
			return false;

		// Refuse un index qui ne correspond à aucun sommet.
		for (int i = 0; i < nombreIndex; ++i) {
			if (index[i] >= static_cast<unsigned int>(nombreSommets))
				return false;
		}

		// Crée et lie le VAO avant de configurer les tampons.
		glGenVertexArrays(1, &mVao);
		if (mVao == 0)
			return false;
		glBindVertexArray(mVao);

		// Copie les données des sommets dans le VBO.
		glGenBuffers(1, &mVbo);
		if (mVbo == 0)
			return false;
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER,
					static_cast<GLsizeiptr>(sizeof(Sommet) *
											static_cast<std::size_t>(nombreSommets)),
					sommets, GL_STATIC_DRAW);

		// Décrit l'attribut de position.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
							static_cast<GLsizei>(sizeof(Sommet)),
							reinterpret_cast<const void *>(offsetof(Sommet, x)));
		glEnableVertexAttribArray(0);

		// Décrit l'attribut de couleur.
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
							static_cast<GLsizei>(sizeof(Sommet)),
							reinterpret_cast<const void *>(offsetof(Sommet, r)));
		glEnableVertexAttribArray(1);

		// Crée l'EBO : son association est enregistrée dans le VAO courant.
		glGenBuffers(1, &mEbo);
		if (mEbo == 0)
			return false;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					static_cast<GLsizeiptr>(sizeof(unsigned int) *
											static_cast<std::size_t>(nombreIndex)),
					index, GL_STATIC_DRAW);

		// Important : ne pas délier GL_ELEMENT_ARRAY_BUFFER avant ou après ceci.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mNombre = nombreIndex;
		mIndex32 = true;
		return true;
	}

	// Libère maintenant aussi le tampon d'index.
	void Maillage::Detruire() {
		if (mEbo != 0) {
			glDeleteBuffers(1, &mEbo);
			mEbo = 0;
		}

		if (mVbo != 0) {
			glDeleteBuffers(1, &mVbo);
			mVbo = 0;
		}

		if (mVao != 0) {
			glDeleteVertexArrays(1, &mVao);
			mVao = 0;
		}
		mIndex32 = false;

		mNombre = 0;
	}

	// Choisit le dessin indexé ou non selon la présence d'un EBO.
	void Maillage::Dessiner() const {
		if (mVao == 0)
			return;

		glBindVertexArray(mVao);

		if (mEbo != 0) {
			const GLenum typeIndex = mIndex32 ? GL_UNSIGNED_INT
											: GL_UNSIGNED_SHORT;

			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mNombre),
						typeIndex, reinterpret_cast<const void *>(0));
		} else {
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mNombre));
		}

		glBindVertexArray(0);
	}

} // namespace monrhi