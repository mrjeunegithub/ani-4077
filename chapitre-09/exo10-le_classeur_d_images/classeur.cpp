#include <iostream>
#include <map>
#include <string>

std::string determinerEspace(const std::string& nom)
{
    std::size_t position = nom.find_last_of('_');

    if (position == std::string::npos)
    {
        return "SRGB";
    }

    std::string suffixe = nom.substr(position + 1);

    if (suffixe == "normal"
        || suffixe == "rugosite"
        || suffixe == "hauteur"
        || suffixe == "metal"
        || suffixe == "occlusion")
    {
        return "LINEAIRE";
    }

    return "SRGB";
}

int main()
{
    int nombreCommandes;
    std::cin >> nombreCommandes;

    std::map<std::string, int> references;
    int creations = 0;
    int reutilisations = 0;
    int creationsSrgb = 0;
    int creationsLineaires = 0;

    for (int i = 0; i < nombreCommandes; ++i)
    {
        std::string commande;
        std::string nom;
        std::cin >> commande >> nom;

        if (commande == "DEMANDE")
        {
            auto texture = references.find(nom);

            if (texture != references.end())
            {
                ++texture->second;
                ++reutilisations;

                std::cout << "REUTILISE " << nom
                          << " REFS " << texture->second << '\n';
            }
            else
            {
                references[nom] = 1;
                ++creations;

                std::string espace = determinerEspace(nom);
                if (espace == "SRGB")
                {
                    ++creationsSrgb;
                }
                else
                {
                    ++creationsLineaires;
                }

                std::cout << "CREE " << nom
                          << " ESPACE " << espace
                          << " REFS 1\n";
            }
        }
        else if (commande == "RENDS")
        {
            auto texture = references.find(nom);

            if (texture == references.end())
            {
                std::cout << "RENDS " << nom << " INCONNU\n";
            }
            else
            {
                --texture->second;

                if (texture->second == 0)
                {
                    references.erase(texture);
                    std::cout << "DETRUIT " << nom << '\n';
                }
                else
                {
                    std::cout << "RENDS " << nom
                              << " REFS " << texture->second << '\n';
                }
            }
        }
    }

    std::cout << "CREATIONS " << creations << '\n';
    std::cout << "REUTILISATIONS " << reutilisations << '\n';
    std::cout << "VIVANTES " << references.size() << '\n';
    std::cout << "SRGB " << creationsSrgb << '\n';
    std::cout << "LINEAIRES " << creationsLineaires << '\n';

    return 0;
}
