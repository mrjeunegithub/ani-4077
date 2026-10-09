#include <iostream>

int CodeVersion(std::string version);

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
                std::cout<< nom << " " << codeDemande <<" " <<  codeRapporte << " " << "ACCEPTE"<< std::endl;
                accepte++;
            }
        }
        else{
            std::cout<< nom << " " << codeDemande <<" " <<  codeRapporte << " " << "EXACT"<< std::endl;
            accepte++;
        }
    }
    std::cout<< "REFUSES: " << refuses << std::endl;
    std::cout<< "SUSPECTS: " << suspects << std::endl;
    std::cout<< "ACCEPTABLES: " << accepte << std::endl;

    return 0;
}

int CodeVersion(std::string version){
    int point = version.find('.');
    int majeur = std::stoi(version.substr(0, point));
    int mineur = std::stoi(version.substr(point+1));
    return majeur*10 + mineur;
}