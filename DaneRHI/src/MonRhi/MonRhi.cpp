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