## Exercice 6 Le fichier oublié

J'ai créé un fichier `Inutile.cpp` dans lequel j'ai défini une fonction que j'ai initialiser dans MonRhi.h

#include "MonRhi/MonRhi.h"

void Neant(){
    std::cout<<"Je suis parfaitement inutile, c'est terrible!"<< std::endl;
}

J'ai ensuite fait un **jenga build** après avoir vérifié les tailles des fichiers demandés. Je les ai vérifiés de nouveau apres et voici le resultat.

## avant 
**MonRhi.lib : 84ko**
**essai.exe: 142 ko**

## Apres
**MonRhi.lib : 98ko**
**essai.exe: 142 ko**

On constate que la taille de `MonRhi.lib` a augmenté avec l'ajout de lu fichier Inutile. Et le fichier essai.exe, lui est resté inchangé

Cela montre que le compilateur a compilé chaque fichier de MonRhi pour formé la lib. Mais le lieur lui ne lie que ce dont on a besoin et a donc ecarté la bibliotèque qui n'est jamais appelé. 
