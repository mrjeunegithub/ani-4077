#include "MonRhi/MonRhi.h"


//#include <iostream>
//#include <string>


struct Format{
    int numero ;
    int manque;
    int exes;
};


int main() {
    int dCouleur, dProfondeur, dPochoir;
    bool dDouble = 0;
    int choix = 0;
    std::cin>>dCouleur >> dProfondeur >> dPochoir >> dDouble;

    int N;
    std::cin >> N;

    // bool dc = false;
    // bool format = false;
    // bool wgl = false;
    // bool gl = false;

    
    for (int i = 1; i <= N; i++) {
        
        int rNumero, rCouleur, rProfondeur, rPochoir;
        bool rDouble;

        std::cin>>rNumero >> rCouleur >> rProfondeur >> rPochoir >> rDouble;
        int manque = (dCouleur - rCouleur)+ (dProfondeur - rProfondeur) + (dPochoir - rPochoir);
        if (manque <= 0){
            manque = 0;
        }
        int exes = (rCouleur - dCouleur)+ (rProfondeur - dProfondeur) + (rPochoir - dPochoir);
        if (exes < 0){
            exes = 0;
        }

        if (dDouble != rDouble) {
            continue;
        }
    }
    if (choix == 0) {
        std::cout << "AUCUN FORMAT\n";
    }
    
    return 0;
}
