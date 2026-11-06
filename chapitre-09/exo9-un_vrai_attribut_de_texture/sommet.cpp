#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombreAttributs;
    std::cin >> nombreAttributs;

    std::vector<std::string> noms(nombreAttributs);
    std::vector<int> composantes(nombreAttributs);

    int composantesAvant = 0;

    for (int i = 0; i < nombreAttributs; ++i)
    {
        std::cin >> noms[i] >> composantes[i];

        int decalage = composantesAvant * 4;

        std::cout << "ATTRIB " << i
                  << ' ' << noms[i]
                  << " COMPOSANTES " << composantes[i]
                  << " DECALAGE " << decalage
                  << '\n';

        composantesAvant += composantes[i];
    }

    long long nombreSommets;
    std::cin >> nombreSommets;

    long long pas = static_cast<long long>(composantesAvant) * 4;
    long long tailleTampon = nombreSommets * pas;

    std::cout << "PAS " << pas << '\n';
    std::cout << "TAMPON " << tailleTampon << '\n';

    return 0;
}
