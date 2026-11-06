#include <iostream>
#include <string>

int main()
{
    int nombreTextures;
    std::cin >> nombreTextures;

    long long totalExact = 0;
    long long totalSansMipmaps = 0;

    for (int i = 0; i < nombreTextures; ++i)
    {
        std::string nom;
        long long largeur;
        long long hauteur;
        std::string mipmaps;

        std::cin >> nom >> largeur >> hauteur >> mipmaps;

        long long base = largeur * hauteur * 4;
        long long exact = base;
        int nombreNiveaux = 1;

        if (mipmaps == "OUI")
        {
            long long largeurNiveau = largeur;
            long long hauteurNiveau = hauteur;

            while (largeurNiveau > 1 || hauteurNiveau > 1)
            {
                largeurNiveau = largeurNiveau / 2;
                hauteurNiveau = hauteurNiveau / 2;

                if (largeurNiveau < 1)
                {
                    largeurNiveau = 1;
                }

                if (hauteurNiveau < 1)
                {
                    hauteurNiveau = 1;
                }

                exact += largeurNiveau * hauteurNiveau * 4;
                ++nombreNiveaux;
            }
        }

        long long estime = base;

        if (mipmaps == "OUI")
        {
            estime = base + base / 3;
        }

        long long ecart = estime - exact;

        std::cout << nom
                  << " NIVEAUX " << nombreNiveaux
                  << " EXACT " << exact
                  << " ESTIME " << estime
                  << " ECART " << ecart
                  << '\n';

        totalExact += exact;
        totalSansMipmaps += base;
    }

    std::cout << "TOTAL " << totalExact << '\n';
    std::cout << "SANS MIPMAPS " << totalSansMipmaps << '\n';

    if (nombreTextures == 0)
    {
        std::cout << "SURCOUT AUCUN\n";
    }
    else
    {
        long long surcout =
            (totalExact - totalSansMipmaps) * 100 / totalSansMipmaps;

        std::cout << "SURCOUT " << surcout << " %\n";
    }

    return 0;
}