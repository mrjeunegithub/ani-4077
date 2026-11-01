// =============================================================================
//  Étape 05 — chapitre 6 : des sommets, un tampon, et la recette pour les lire.
//
//  TROIS OBJETS, ET ON LES CONFOND TOUT LE TEMPS
//  =============================================
//  Pour dessiner un triangle il faut trois choses distinctes, et la moitié des
//  premiers bogues vient de croire que c'en est une seule.
//
//    1. VOS DONNÉES, dans la mémoire de votre programme. Un tableau de
//       flottants. OpenGL ne les voit pas.
//
//    2. LE TAMPON (VBO, Vertex Buffer Object). Un bloc de mémoire du côté de
//       la carte graphique. On y COPIE vos données. À partir de là, modifier
//       votre tableau ne change plus rien à l'écran.
//
//    3. L'OBJET DE TABLEAU DE SOMMETS (VAO, Vertex Array Object). Il ne
//       contient AUCUNE donnée. C'est une RECETTE : « la position est faite de
//       trois flottants, elle commence à l'octet 0, et chaque sommet occupe
//       24 octets ». Sans lui, le tampon n'est qu'une suite d'octets dont
//       personne ne sait quoi faire.
//
//  L'image qui a fonctionné avec la promotion : le tampon est le carton de
//  déménagement, le VAO est l'étiquette qui dit ce qu'il y a dedans et dans
//  quel ordre. Un carton sans étiquette est inutilisable ; une étiquette sans
//  carton ne décrit rien.
// =============================================================================
#pragma once

namespace monrhi {

	struct Sommet {
		float x, y, z;
		float r, v, b;
	};

	class Maillage {
		public:
			Maillage() = default;
			~Maillage();

			Maillage(const Maillage &) = delete;
			Maillage &operator=(const Maillage &) = delete;

			bool Creer(const Sommet *sommets, int nombre);

			// Crée un maillage à partir de sommets uniques et d'index.
			bool CreerIndexe(const Sommet *sommets, int nombreSommets,
							 const unsigned short *index, int nombreIndex);
			// Ajoute à côté de CreerIndexe :
			bool CreerIndexe32(const Sommet *sommets, int nombreSommets,
							const unsigned int *index, int nombreIndex);	

			void Detruire();

			void Dessiner() const;

			bool EstValide() const { return mVao != 0 && mVbo != 0; }

			int Nombre() const { return mNombre; }

			unsigned int IdTampon() const { return mVbo; }
			unsigned int IdTableau() const { return mVao; }

		private:
			unsigned int mVao = 0;
			unsigned int mVbo = 0;

			// Zéro indique que ce maillage n'utilise pas d'index.
			unsigned int mEbo = 0;

			// Nombre de sommets sans EBO, nombre d'index avec EBO.
			int mNombre = 0;
			// true si l'EBO contient des unsigned int de 4 octets.
			bool mIndex32 = false;
	};

} // namespace monrhi