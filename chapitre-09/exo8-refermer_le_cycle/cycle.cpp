#include <cmath>
#include <iostream>

int arrondirOctet(double valeur)
{
    return static_cast<int>(std::floor(valeur * 255.0 + 0.5));
}

double decoderSrgb(double x)
{
    if (x <= 0.04045)
    {
        return x / 12.92;
    }

    return std::pow((x + 0.055) / 1.055, 2.4);
}

double encoderSrgbExact(double lineaire)
{
    if (lineaire <= 0.0031308)
    {
        return lineaire * 12.92;
    }

    return 1.055 * std::pow(lineaire, 1.0 / 2.4) - 0.055;
}

int main()
{
    int nombre;
    std::cin >> nombre;

    int identiques = 0;
    int ecartMaximum = -1;
    int octetEcartMaximum = 0;

    for (int i = 0; i < nombre; ++i)
    {
        int octet;
        std::cin >> octet;

        double x = octet / 255.0;
        double lineaire = decoderSrgb(x);

        int decode = arrondirOctet(lineaire);
        int gamma = arrondirOctet(std::pow(lineaire, 1.0 / 2.2));
        int exact = arrondirOctet(encoderSrgbExact(lineaire));
        int ecart = gamma - octet;

        std::cout << octet
                  << " DECODE " << decode
                  << " GAMMA " << gamma
                  << " EXACT " << exact
                  << " ECART " << ecart << '\n';

        if (gamma == octet)
        {
            ++identiques;
        }

        int valeurAbsolue = std::abs(ecart);
        if (valeurAbsolue > ecartMaximum)
        {
            ecartMaximum = valeurAbsolue;
            octetEcartMaximum = octet;
        }
    }

    if (nombre == 0)
    {
        ecartMaximum = 0;
    }

    std::cout << "IDENTIQUES " << identiques << '\n';
    std::cout << "ECART MAX " << ecartMaximum
              << " POUR " << octetEcartMaximum << '\n';

    return 0;
}
