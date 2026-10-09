#include "MonRhi/MonRhi.h"

int main(){
    //Somme();
    //Transition();
    int N;
    std::cin>> N;
    int refuses = 0;
    int suspects = 0;
    int accepte = 0;

    for(int i=0; i<N; i++){
        //int majeur, mineur;
        std::string nom, chemin, demande, rapporte;
        std::cin>>nom >> chemin >> demande >> rapporte;

        int codeDemande = CodeVersion(demande);
        int codeRapporte = CodeVersion(rapporte);
        if(codeDemande > codeRapporte){
            std::cout<< nom << " " << codeDemande << " " << codeRapporte << " " << "TROP VIEUX"<< std::endl;
            refuses++;
        }
        else if(codeDemande < codeRapporte){
            if(chemin == "WGL"){
                std::cout<< nom << " " << codeDemande <<" " <<  codeRapporte << " " << "CONTEXTE PROVISOIRE"<< std::endl;
                suspects++;
            }
            else{
                std::cout<< nom << " " << codeDemande <<" " <<  codeRapporte << " " << "ACCEPTABLE"<< std::endl;
                accepte++;
            }
        }
        else{
            std::cout<< nom << " " << codeDemande <<" " <<  codeRapporte << " " << "EXACT"<< std::endl;
            accepte++;
        }
    }
    std::cout<< "Refuses: " << refuses << std::endl;
    std::cout<< "Suspects: " << suspects << std::endl;
    std::cout<< "Acceptés: " << accepte << std::endl;

    return 0;
}