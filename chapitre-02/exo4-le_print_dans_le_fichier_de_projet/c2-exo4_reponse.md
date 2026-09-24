## Exercice 4 Le print dans le fichier projet

J'ai ajouté les lignes demandés dans mon fichier .jenga

rom Jenga import *
`import sys`
`print("configurations :", ["Debug", "Release"], file=sys.stderr)`

with workspace("MonRhiWks", location="."):
       configurations(["Debug", "Release"])

       # La bibliotheque : du code compile, sans main.
       with project("MonRhi"):
              staticlib()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/MonRhi/**.cpp"])...

Puis j'ai lance **jenga info** et j'ai obtenu

PS C:\dane\ecole\Teguis\Exercices\DaneRhi> jenga info

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

`configurations : ['Debug', 'Release']`
========================== Jenga Workspace: MonRhiWks ==========================

Location: C:\dane\ecole\Teguis\Exercices\DaneRHI
Entry file: C:\dane\ecole\Teguis\Exercices\DaneRHI\MonRhiWks.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: 
Target Architectures: 


Projects
------------------------------------------------------------
Name     Kind         Language   Test   External
================================================
MonRhi   StaticLib    C++        No     No
Essai    ConsoleApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running


On voit bien affiché **configurations : ['Debug', 'Release']** juste après la bannière de Jenga avant les informations du projet. Cela nous montre encore que un fichier jenga est un fichier python et que un print marche sans soucis.

J'ai pas compris la deuxième partie de l'exercice. J'ai essay de cherché le terme **rhiDeps** dans le fichier NkRHI.jenga de Nkentseu pour que ca me donne une piste mais j'ai rien trouvé.