#include <iostream>
#include <string>

int compterNiveauxComplets(int largeur, int hauteur)
{
    int nombre = 1;

    while (largeur > 1 || hauteur > 1)
    {
        largeur = largeur / 2;
        hauteur = hauteur / 2;

        if (largeur < 1)
        {
            largeur = 1;
        }

        if (hauteur < 1)
        {
            hauteur = 1;
        }

        ++nombre;
    }

    return nombre;
}

int main()
{
    int nombreTextures;
    std::cin >> nombreTextures;

    int nombreTexturesNoires = 0;
    int niveauxPerdus = 0;

    for (int i = 0; i < nombreTextures; ++i)
    {
        std::string nom;
        int largeur;
        int hauteur;
        std::string filtre;
        std::string niveauxTexte;

        std::cin >> nom
                 >> largeur
                 >> hauteur
                 >> filtre
                 >> niveauxTexte;

        int niveauxComplets =
            compterNiveauxComplets(largeur, hauteur);

        int niveauxDisponibles;

        if (niveauxTexte == "GENERE")
        {
            niveauxDisponibles = niveauxComplets;
        }
        else
        {
            niveauxDisponibles = std::stoi(niveauxTexte);

            if (niveauxDisponibles > niveauxComplets)
            {
                niveauxDisponibles = niveauxComplets;
            }
        }

        if (filtre == "DEFAUT")
        {
            filtre = "GL_NEAREST_MIPMAP_LINEAR";
        }

        bool filtreAvecMipmaps =
            filtre.find("MIPMAP") != std::string::npos;

        bool textureNoire = false;
        int niveauxManquants = 0;

        if (filtreAvecMipmaps)
        {
            niveauxManquants =
                niveauxComplets - niveauxDisponibles;

            textureNoire = niveauxManquants > 0;
        }

        if (textureNoire)
        {
            std::cout << nom << " NOIRE MANQUE "
                      << niveauxManquants << '\n';

            ++nombreTexturesNoires;
        }
        else
        {
            std::cout << nom << " COMPLETE\n";

            if (!filtreAvecMipmaps)
            {
                niveauxPerdus += niveauxDisponibles - 1;
            }
        }
    }

    std::cout << "NOIRES " << nombreTexturesNoires << '\n';
    std::cout << "NIVEAUX PERDUS " << niveauxPerdus << '\n';
    std::cout << "GL_GET_ERROR GL_NO_ERROR\n";

    return 0;
}