#include "MonRhi/MonRhi.h"


#include <iostream>
#include <string>
using namespace std;

const int MAX = 10000;

struct Contexte {
    string nom;
    bool core;
    bool vivant;
};

int main() {
    int N;
    cin >> N;

    bool dc = false;
    bool format = false;
    bool wgl = false;
    bool gl = false;

    Contexte contextes[MAX];
    int nbContextes = 0;
    int erreurs = 0;
    string courant = "AUCUN";

    for (int i = 1; i <= N; i++) {
        string commande, nom;
        cin >> commande;

        string resultat = "OK";

        if (commande == "GETDC") {
            dc = true;
        }
        else if (commande == "FORMAT") {
            if (!dc)
                resultat = "ERREUR PAS DE DC";
            else if (format)
                resultat = "ERREUR FORMAT DEJA POSE";
            else
                format = true;
        }
        else if (commande == "CREER" ||
                 commande == "CREER_ATTRIBS") {
            cin >> nom;

            if (!format) {
                resultat = "ERREUR PAS DE FORMAT";
            }
            else if (commande == "CREER_ATTRIBS" && !wgl) {
                resultat = "ERREUR EXTENSION NON CHARGEE";
            }
            else {
                bool existe = false;

                for (int j = 0; j < nbContextes; j++) {
                    if (contextes[j].nom == nom &&
                        contextes[j].vivant) {
                        existe = true;
                        break;
                    }
                }

                if (existe) {
                    resultat = "ERREUR NOM PRIS";
                }
                else {
                    contextes[nbContextes].nom = nom;
                    contextes[nbContextes].core =
                        (commande == "CREER_ATTRIBS");
                    contextes[nbContextes].vivant = true;
                    nbContextes++;
                }
            }
        }
        else if (commande == "COURANT") {
            cin >> nom;

            if (nom == "AUCUN") {
                courant = "AUCUN";
            }
            else {
                bool existe = false;

                for (int j = 0; j < nbContextes; j++) {
                    if (contextes[j].nom == nom &&
                        contextes[j].vivant) {
                        existe = true;
                        break;
                    }
                }

                if (!existe)
                    resultat = "ERREUR CONTEXTE INCONNU";
                else
                    courant = nom;
            }
        }
        else if (commande == "CHARGER_WGL") {
            if (courant == "AUCUN")
                resultat = "ERREUR PAS DE CONTEXTE COURANT";
            else
                wgl = true;
        }
        else if (commande == "CHARGER_GL") {
            if (courant == "AUCUN")
                resultat = "ERREUR PAS DE CONTEXTE COURANT";
            else
                gl = true;
        }
        else if (commande == "DETRUIRE") {
            cin >> nom;

            int indice = -1;

            for (int j = 0; j < nbContextes; j++) {
                if (contextes[j].nom == nom &&
                    contextes[j].vivant) {
                    indice = j;
                    break;
                }
            }

            if (indice == -1) {
                resultat = "ERREUR CONTEXTE INCONNU";
            }
            else if (courant == nom) {
                resultat = "ERREUR CONTEXTE COURANT";
            }
            else {
                contextes[indice].vivant = false;
            }
        }
        else if (commande == "GL") {
            cin >> nom;

            if (courant == "AUCUN" || !gl)
                resultat = "PLANTAGE ADRESSE ZERO";
        }

        if (resultat != "OK")
            erreurs++;

        cout << i << " " << resultat << '\n';
    }

    cout << "ERREURS " << erreurs << '\n';
    cout << "COURANT " << courant << '\n';

    if (courant == "AUCUN") {
        cout << "PROFIL AUCUN\n";
    }
    else {
        for (int i = 0; i < nbContextes; i++) {
            if (contextes[i].nom == courant &&
                contextes[i].vivant) {
                cout << "PROFIL "
                     << (contextes[i].core ? "CORE" : "COMPATIBILITE")
                     << '\n';
                break;
            }
        }
    }

    int vivants = 0;

    for (int i = 0; i < nbContextes; i++) {
        if (contextes[i].vivant)
            vivants++;
    }

    cout << "VIVANTS " << vivants << '\n';

    return 0;
}
