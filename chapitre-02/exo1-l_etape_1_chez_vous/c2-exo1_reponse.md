### Exercice 1 L'étape 1 chez vous

## Jenga info

J'ai copié le workspace present dans le cours et l'ai appliqué chez moi. Puis, j'ai entré la commane "jenga info". Voici le résultat

**========================== Jenga Workspace: MonRhiWks ==========================**

Location: C:\dane\ecole\Teguis\Exercices\DaneRHI
Entry file: C:\dane\ecole\Teguis\Exercices\DaneRHI\MonRhiWks.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: 
Target Architectures: 


**Projects**
------------------------------------------------------------
Name     Kind         Language   Test   External
================================================
MonRhi   StaticLib    C++        No     No
Essai    ConsoleApp   C++        No     No


**Available Toolchains**
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


**Daemon**
------------------------------------------------------------
Status: Not running


Comme mentionné dans le cours, on a la ce que jenga a compris du projet. C'est tres interessant à observer et il est evident que cette commande s'averera très utiles lors des differents travaux pour

**Verifier que la structure que je voulais mettre en place est effective**
**S'assurer que j'ai tout ce qu'il faut pour construire mes projets (La toolchain)**...


## Jenga build

J'ai ensuite lancé un **jenga build** pour construire ce projet. Mais avant j'ai pris soin de cronstruire une petite architechture basée sur le contenu du fichier jenga. Et j'ai obtenu ceci

PS C:\dane\ecole\Teguis\exercices\DaneRhi> jenga build

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (2 projects):
  1. MonRhi [STATIC_LIB] → 
  2. Essai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonRhi                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: MonRhi.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\MonRhi.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.32s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Essai                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

No source files found for project Essai

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  2/2
Time:           0.33s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════


On constate ici que la commande jenga build, en plus de construire notre projet nous donne tout un tas d'information utiles. Elle nous detaille en quelque sorte son processus de travail. Nous avons donc

**Le chargement du workspace**
**Les configurations des build**
**L'ordre de compilation des projets et leurs types**
**Puis la compilation de chaque fichier par projet**
**A la fin un petit bilan de la compilation**

Ici la compilation a été un **succès**, on a le temps de compilation **0.33s** et les deux projets ont été construit malgré l'abscence de fichier source dans le projet Essai.

## Jenga Run

J'ai modifi le projet en ajoutant un fichier main.cpp dans le projet Essai

#include "MonRhi/MonRhi.h"

int main(){
    std::cout<<"Hello World from Essai!"<<std::endl;
}

J'ai ensuite recompiler puis lancé la commande **jenga run** et voici le retour


PS C:\dane\ecole\Teguis\exercices\DaneRhi> jenga run  

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Essai.exe
     C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Bin\Debug-Windows\Essai\Essai.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Hello World from Essai!

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.13s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


On peut donc observer le cheminement de travail de jenga run qui 
**Donne le nom du fichier qu'il execute ainsi que son emplacement**
**Affiche le resultat de l'execution en elle meme**
**En enfin se conclue en precisant si tout c'est bien passé**

Ici l'execution s'est **terminé normalement** en **0.13s**