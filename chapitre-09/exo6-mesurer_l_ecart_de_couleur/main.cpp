#include <cmath>
#include <iostream>
#include <string>

int convertirComposante(int octet)
{
    double valeur = octet / 255.0;
    double lineaire;

    if (valeur <= 0.04045)
    {
        lineaire = valeur / 12.92;
    }
    else
    {
        lineaire = std::pow(
            (valeur + 0.055) / 1.055,
            2.4
        );
    }

    return static_cast<int>(std::floor(lineaire * 255.0 + 0.5));
}

int main()
{
    int nombrePixels;
    std::cin >> nombrePixels;

    long long totalRouge = 0;
    long long totalVert = 0;
    long long totalBleu = 0;

    for (int i = 0; i < nombrePixels; ++i)
    {
        int rougeLu;
        int vertLu;
        int bleuLu;

        std::cin >> rougeLu >> vertLu >> bleuLu;

        int rougeEcrit = convertirComposante(rougeLu);
        int vertEcrit = convertirComposante(vertLu);
        int bleuEcrit = convertirComposante(bleuLu);

        int ecartRouge = rougeEcrit - rougeLu;
        int ecartVert = vertEcrit - vertLu;
        int ecartBleu = bleuEcrit - bleuLu;

        totalRouge += ecartRouge;
        totalVert += ecartVert;
        totalBleu += ecartBleu;

        std::cout << "LU "
                  << rougeLu << ' ' << vertLu << ' ' << bleuLu
                  << " ECRIT "
                  << rougeEcrit << ' ' << vertEcrit << ' ' << bleuEcrit
                  << " ECART "
                  << ecartRouge << ' ' << ecartVert << ' ' << ecartBleu
                  << '\n';
    }

    std::cout << "ECART TOTAL "
              << totalRouge << ' '
              << totalVert << ' '
              << totalBleu << '\n';

    std::string plusTouchee = "AUCUNE";

    if (totalRouge != 0 || totalVert != 0 || totalBleu != 0)
    {
        plusTouchee = "ROUGE";

        if (totalVert < totalRouge)
        {
            plusTouchee = "VERT";
        }

        if ((plusTouchee == "ROUGE" && totalBleu < totalRouge)
            || (plusTouchee == "VERT" && totalBleu < totalVert))
        {
            plusTouchee = "BLEU";
        }
    }

    std::cout << "PLUS TOUCHEE " << plusTouchee << '\n';

    return 0;
}