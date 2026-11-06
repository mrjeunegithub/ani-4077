#include <iostream>
#include <vector>

int bornerIndice(long long indice, int taille)
{
    if (indice < 0)
    {
        return 0;
    }

    if (indice >= taille)
    {
        return taille - 1;
    }

    return static_cast<int>(indice);
}

long long divisionPlancher(
    long long numerateur,
    long long denominateur
)
{
    long long quotient = numerateur / denominateur;
    long long reste = numerateur % denominateur;

    if (reste < 0)
    {
        --quotient;
    }

    return quotient;
}

int lireLineaire(
    const std::vector<std::vector<int>>& texture,
    int largeur,
    int hauteur,
    long long u,
    long long v
)
{
    long long X = 2LL * u * largeur - 1000;
    long long Y = 2LL * v * hauteur - 1000;

    long long colonne0 = divisionPlancher(X, 2000);
    long long ligne0 = divisionPlancher(Y, 2000);

    long long fx = X - colonne0 * 2000;
    long long fy = Y - ligne0 * 2000;

    int c00 = texture[
        bornerIndice(ligne0, hauteur)
    ][
        bornerIndice(colonne0, largeur)
    ];

    int c10 = texture[
        bornerIndice(ligne0, hauteur)
    ][
        bornerIndice(colonne0 + 1, largeur)
    ];

    int c01 = texture[
        bornerIndice(ligne0 + 1, hauteur)
    ][
        bornerIndice(colonne0, largeur)
    ];

    int c11 = texture[
        bornerIndice(ligne0 + 1, hauteur)
    ][
        bornerIndice(colonne0 + 1, largeur)
    ];

    long long poids00 = (2000 - fx) * (2000 - fy);
    long long poids10 = fx * (2000 - fy);
    long long poids01 = (2000 - fx) * fy;
    long long poids11 = fx * fy;

    long long somme =
        c00 * poids00
        + c10 * poids10
        + c01 * poids01
        + c11 * poids11;

    return static_cast<int>((somme + 2000000) / 4000000);
}

int main()
{
    int largeur;
    int hauteur;
    int nombrePoints;

    std::cin >> largeur >> hauteur >> nombrePoints;

    std::vector<std::vector<int>> texture(
        hauteur,
        std::vector<int>(largeur)
    );

    for (int j = 0; j < hauteur; ++j)
    {
        for (int i = 0; i < largeur; ++i)
        {
            std::cin >> texture[j][i];
        }
    }

    int nombreSurs = 0;
    int nombreFrontieres = 0;

    for (int point = 0; point < nombrePoints; ++point)
    {
        long long u;
        long long v;

        std::cin >> u >> v;

        long long colonneProche = u * largeur / 1000;
        long long ligneProche = v * hauteur / 1000;

        int valeurProche = texture[
            bornerIndice(ligneProche, hauteur)
        ][
            bornerIndice(colonneProche, largeur)
        ];

        int valeurLineaire =
            lireLineaire(texture, largeur, hauteur, u, v);

        if (valeurProche == valeurLineaire)
        {
            ++nombreSurs;

            std::cout << u << ' ' << v
                      << " PROCHE " << valeurProche
                      << " LINEAIRE " << valeurLineaire
                      << " SUR\n";
        }
        else
        {
            ++nombreFrontieres;

            std::cout << u << ' ' << v
                      << " PROCHE " << valeurProche
                      << " LINEAIRE " << valeurLineaire
                      << " FRONTIERE\n";
        }
    }

    std::cout << "SURS " << nombreSurs << '\n';
    std::cout << "FRONTIERES " << nombreFrontieres << '\n';

    return 0;
}