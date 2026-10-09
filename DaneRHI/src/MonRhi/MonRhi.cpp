#include "MonRhi/MonRhi.h"

namespace monrhi {
    const char* Version()          { return "MonRhi 0.2"; }
    std::string BackendActif()     { return "aucun"; }
}

void Somme(){
    long long somme = 0;
    for(long long i=0; i<100000000; i++){
        somme += i;
    }
    std::cout<<somme<<std::endl;
}

void Transition(){
    PrintUtil();
}

int CodeVersion(std::string version){
    int point = version.find('.');
    int majeur = std::stoi(version.substr(0, point));
    int mineur = std::stoi(version.substr(point+1));
    return majeur*10 + mineur;
}
