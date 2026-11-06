#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombreEchantillonneurs;
    int nombreAppels;

    std::cin >> nombreEchantillonneurs >> nombreAppels;

    std::vector<std::string> noms(nombreEchantillonneurs);
    std::vector<int> uniteEchantillonneur(nombreEchantillonneurs, 0);

    for (int i = 0; i < nombreEchantillonneurs; ++i)
    {
        std::cin >> noms[i];
    }

    std::vector<int> textureParUnite(16, 0);
    int uniteActive = 0;

    int nombreDessins = 0;
    int dessinsJustes = 0;
    int dessinsFaux = 0;
    int uniform1fIgnores = 0;

    for (int appel = 0; appel < nombreAppels; ++appel)
    {
        std::string commande;
        std::cin >> commande;

        if (commande == "ACTIVE")
        {
            std::cin >> uniteActive;
        }
        else if (commande == "BIND")
        {
            int texture;
            std::cin >> texture;

            textureParUnite[uniteActive] = texture;
        }
        else if (commande == "UNIFORM1I")
        {
            std::string nom;
            int unite;

            std::cin >> nom >> unite;

            for (int i = 0; i < nombreEchantillonneurs; ++i)
            {
                if (noms[i] == nom)
                {
                    uniteEchantillonneur[i] = unite;
                    break;
                }
            }
        }
        else if (commande == "UNIFORM1F")
        {
            std::string nom;
            int unite;

            std::cin >> nom >> unite;
            ++uniform1fIgnores;
        }
        else if (commande == "DESSINE")
        {
            std::vector<std::string> erreurs;

            for (int i = 0; i < nombreEchantillonneurs; ++i)
            {
                int textureAttendue;
                std::cin >> textureAttendue;

                int unite = uniteEchantillonneur[i];
                int textureLue = textureParUnite[unite];

                if (textureLue != textureAttendue)
                {
                    erreurs.push_back(
                        noms[i] + "="
                        + std::to_string(textureLue) + "/"
                        + std::to_string(textureAttendue)
                    );
                }
            }

            ++nombreDessins;

            if (erreurs.empty())
            {
                ++dessinsJustes;
                std::cout << "DESSIN "
                          << nombreDessins
                          << " JUSTE\n";
            }
            else
            {
                ++dessinsFaux;
                std::cout << "DESSIN "
                          << nombreDessins
                          << " FAUX";

                for (const std::string& erreur : erreurs)
                {
                    std::cout << ' ' << erreur;
                }

                std::cout << '\n';
            }
        }
    }

    std::cout << "JUSTES " << dessinsJustes << '\n';
    std::cout << "FAUX " << dessinsFaux << '\n';
    std::cout << "UNIFORM1F IGNORES "
              << uniform1fIgnores << '\n';

    return 0;
}