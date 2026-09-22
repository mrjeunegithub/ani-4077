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


On constate ici que la commande jenga bbuild, en plus de construire notre projet nous donne tout un d'information utiles. Elle nous detaille en quelque sorte son processus de travail. Nous avons donc

**Le chargement du workspace**
**Les configurations des build**
**L'ordre de compilation des projets et leurs types**
**Puis la compilation de chaque fichier par projet**
**A la fin un petit bilan de la compilation**

Ici la compilation a été un **succès**, on a le temps de compilation **0.33s** et les deux projets ont été construit malgré l'abscence de fichier source dans le projet Essai.

## Jenga Run

J'ai lancé **jenga run** et obtenu ceci 


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

Executable not found: C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Bin\Debug-Windows\Essai\Essai.exe

J'ai en retour cette erreur qui me signale que il n y a pas d' executable dans le dossier compilé du projet Essai. Et c'est logique, Jenga build signalait deja plus haut que il n'y a pas de fichier source mais ce n'etait pas bloquant. Ici c'est exactement ce avec quoi jenga run travaille et ne peut rien faire s'il n'y a rien à executer.

On note aussi que l'erreur ne se plaint que du projet Essai pourtant il y a deux projet et le projet MonRhi est meme le premier dans la liste! L difference est que MonRhi est est une Static Lib et n' a donc pas vocation a etre excutéé.