#include <iostream>
#include <string>
#include <vector>

long long divisionPlancher(long long numerateur, long long denominateur)
{
    long long quotient = numerateur / denominateur;
    long long reste = numerateur % denominateur;

    if (reste < 0)
    {
        --quotient;
    }

    return quotient;
}

int main()
{
    int largeur;
    int hauteur;
    int correctionChargeur;
    int correctionNuanceur;
    std::string mode;
    int nombreLectures;

    std::cin >> largeur
             >> hauteur
             >> correctionChargeur
             >> correctionNuanceur
             >> mode
             >> nombreLectures;

    std::vector<std::string> image(hauteur);

    for (int ligne = 0; ligne < hauteur; ++ligne)
    {
        std::cin >> image[ligne];
    }

    for (int lecture = 0; lecture < nombreLectures; ++lecture)
    {
        long long u;
        long long v;

        std::cin >> u >> v;

        long long uOriginal = u;
        long long vOriginal = v;

        if (correctionNuanceur == 1)
        {
            v = 1000 - v;
        }

        long long colonne =
            divisionPlancher(u * largeur, 1000);

        long long ligne =
            divisionPlancher(v * hauteur, 1000);

        if (mode == "GL_REPEAT")
        {
            colonne = ((colonne % largeur) + largeur) % largeur;
            ligne = ((ligne % hauteur) + hauteur) % hauteur;
        }
        else
        {
            if (colonne < 0)
            {
                colonne = 0;
            }
            else if (colonne >= largeur)
            {
                colonne = largeur - 1;
            }

            if (ligne < 0)
            {
                ligne = 0;
            }
            else if (ligne >= hauteur)
            {
                ligne = hauteur - 1;
            }
        }

        long long ligneImage;

        if (correctionChargeur == 1)
        {
            ligneImage = hauteur - 1 - ligne;
        }
        else
        {
            ligneImage = ligne;
        }

        char caractere = image[ligneImage][colonne];

        std::cout << uOriginal
                  << ' '
                  << vOriginal
                  << ' '
                  << caractere
                  << '\n';
    }

    int corrections = correctionChargeur + correctionNuanceur;

    std::cout << "CORRECTIONS " << corrections << '\n';

    if (corrections == 1)
    {
        std::cout << "IMAGE DROITE\n";
    }
    else
    {
        std::cout << "IMAGE RETOURNEE\n";
    }

    return 0;
}