#include <iostream>

int main()
{
    long long tailleTexture;
    int nombreAffichages;

    std::cin >> tailleTexture >> nombreAffichages;

    long long coteNiveau = tailleTexture;
    int niveauMaximum = 0;

    while (coteNiveau > 1)
    {
        coteNiveau /= 2;
        ++niveauMaximum;
    }

    int affichagesQuiScintillent = 0;

    for (int i = 0; i < nombreAffichages; ++i)
    {
        long long tailleEcran;
        std::cin >> tailleEcran;

        int niveauChoisi = 0;
        long long coteChoisi = tailleTexture;

        while (coteChoisi / 2 >= tailleEcran)
        {
            coteChoisi /= 2;
            ++niveauChoisi;
        }

        long long unSur = 1;

        if (tailleEcran < tailleTexture)
        {
            long long rapport = tailleTexture / tailleEcran;
            unSur = rapport * rapport;
        }

        if (unSur > 1)
        {
            ++affichagesQuiScintillent;
        }

        std::cout << "ECRAN " << tailleEcran
                  << " NIVEAU " << niveauChoisi
                  << " COTE " << coteChoisi
                  << " UN SUR " << unSur
                  << '\n';
    }

    std::cout << "NIVEAU MAX " << niveauMaximum << '\n';
    std::cout << "SCINTILLENT " << affichagesQuiScintillent << '\n';

    return 0;
}