
#include <iostream>

struct Format {
    int numero;
    int manque;
    int exes;
    int couleur;
    int profondeur;
    int pochoir;
};

int main() {
    int dCouleur, dProfondeur, dPochoir;
    bool dDouble = 0;
    int choix = 0;

    std::cin >> dCouleur >> dProfondeur >> dPochoir >> dDouble;

    int N;
    std::cin >> N;

    Format meilleur;
    meilleur.manque = 0;
    meilleur.exes = 0;
    meilleur.numero = 0;

    for (int i = 1; i <= N; i++) {
        int rNumero, rCouleur, rProfondeur, rPochoir;
        bool rDouble;

        std::cin >> rNumero >> rCouleur >> rProfondeur
                 >> rPochoir >> rDouble;

        if (dDouble != rDouble) {
            continue;
        }

        int manque = (dCouleur - rCouleur)
                   + (dProfondeur - rProfondeur)
                   + (dPochoir - rPochoir);

        if (rCouleur > dCouleur)
            manque -= dCouleur - rCouleur;
        if (rProfondeur > dProfondeur)
            manque -= dProfondeur - rProfondeur;
        if (rPochoir > dPochoir)
            manque -= dPochoir - rPochoir;

        if (manque < 0)
            manque = 0;

        int exes = (rCouleur - dCouleur)
                 + (rProfondeur - dProfondeur)
                 + (rPochoir - dPochoir);

        if (rCouleur < dCouleur)
            exes -= rCouleur - dCouleur;
        if (rProfondeur < dProfondeur)
            exes -= rProfondeur - dProfondeur;
        if (rPochoir < dPochoir)
            exes -= rPochoir - dPochoir;

        if (exes < 0)
            exes = 0;

        if (choix == 0
            || manque < meilleur.manque
            || (manque == meilleur.manque && exes < meilleur.exes)
            || (manque == meilleur.manque && exes == meilleur.exes
                && rNumero < meilleur.numero)) {

            meilleur.numero = rNumero;
            meilleur.manque = manque;
            meilleur.exes = exes;
            meilleur.couleur = rCouleur;
            meilleur.profondeur = rProfondeur;
            meilleur.pochoir = rPochoir;

            choix = 1;
        }
    }

    if (choix == 0) {
        std::cout << "AUCUN FORMAT\n";
        return 0;
    }

    std::cout << "FORMAT " << meilleur.numero << '\n';

    int rabotes = 0;

    std::cout << "couleur " << dCouleur << ' '
              << meilleur.couleur << ' ';

    if (meilleur.couleur == dCouleur)
        std::cout << "EXACT\n";
    else if (meilleur.couleur < dCouleur) {
        std::cout << "RABOTE\n";
        rabotes++;
    }
    else
        std::cout << "PLUS\n";

    std::cout << "profondeur " << dProfondeur << ' '
              << meilleur.profondeur << ' ';

    if (meilleur.profondeur == dProfondeur)
        std::cout << "EXACT\n";
    else if (meilleur.profondeur < dProfondeur) {
        std::cout << "RABOTE\n";
        rabotes++;
    }
    else
        std::cout << "PLUS\n";

    std::cout << "pochoir " << dPochoir << ' '
              << meilleur.pochoir << ' ';

    if (meilleur.pochoir == dPochoir)
        std::cout << "EXACT\n";
    else if (meilleur.pochoir < dPochoir) {
        std::cout << "RABOTE\n";
        rabotes++;
    }
    else
        std::cout << "PLUS\n";

    std::cout << "RABOTES " << rabotes << '\n';

    return 0;
}
