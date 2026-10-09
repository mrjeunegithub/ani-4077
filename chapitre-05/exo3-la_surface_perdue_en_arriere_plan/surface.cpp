#include <iostream>
#include <string>
#include <vector>

struct Evenement {
    int temps;
    std::string type;
};

struct Resultat {
    int images = 0;
    int erreurs = 0;
    int sommeils = 0;
    int rattachements = 0;
};

Resultat simuler(const std::vector<Evenement>& evenements, bool corrige) {
    bool surfaceVivante = true;
    bool attache = true;
    int numeroSurface = 0;
    int numeroAttache = 0;
    Resultat resultat;

    for (const Evenement& evenement : evenements) {
        if (evenement.type == "PERTE") {
            surfaceVivante = false;
        } else if (evenement.type == "RETOUR") {
            surfaceVivante = true;
            ++numeroSurface;
        } else if (corrige && evenement.type == "CACHEE") {
            attache = false;
        } else if (corrige && evenement.type == "MONTREE") {
            if (!attache && surfaceVivante) {
                attache = true;
                numeroAttache = numeroSurface;
                ++resultat.rattachements;
            }
        } else if (evenement.type == "IMAGE") {
            if (corrige && !attache) {
                ++resultat.sommeils;
            } else if (surfaceVivante && numeroAttache == numeroSurface) {
                ++resultat.images;
            } else {
                ++resultat.erreurs;
                if (corrige) {
                    attache = false;
                }
            }
        }
    }

    return resultat;
}

void afficher(const std::string& mode, const Resultat& resultat) {
    std::cout << "MODE " << mode << '\n';
    std::cout << "IMAGES " << resultat.images << '\n';
    std::cout << "ERREURS " << resultat.erreurs << '\n';
    std::cout << "SOMMEILS " << resultat.sommeils << '\n';
    std::cout << "RATTACHEMENTS " << resultat.rattachements << '\n';
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Evenement> evenements(n);
    for (Evenement& evenement : evenements) {
        std::cin >> evenement.temps >> evenement.type;
    }

    afficher("NAIF", simuler(evenements, false));
    afficher("CORRIGE", simuler(evenements, true));
    return 0;
}
