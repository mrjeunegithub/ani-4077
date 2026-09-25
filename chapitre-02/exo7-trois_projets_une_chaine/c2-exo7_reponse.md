## Exercice 7 Trois projets, une chaine

### NB: Mon workspace est desormais present en entier sur mon depot github à https://github.com/mrjeunegithub/ani-4077/tree/main/DaneRhi

J'ai ajouté un troisième projet `MonUtil` donc dépend `MonRhi` Et j' ai ajouté une fonction `PrintUtil()` pour lest tests

with project("MonUtil"):
        staticlib()
        language("C++")
        cppdialect("C++17")
        location(".")
        files(["src/MonUtil/**.cpp"])
        includedirs(["src"])
        objdir("%{wks.location}/Build/Obj/"
                "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/"
                "%{cfg.buildcfg}-%{cfg.system}")

### Pas de 'MonUtil' à Links

J'ai d'abord essayé de compilé sans ajouté **MonUtil** à links et la compilation a échoué

PS C:\dane\ecole\Teguis\exercices\ani-4077\DaneRhi> jenga build  

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

Build Order (3 projects):
  1. MonRhi [STATIC_LIB] → 
  2. MonUtil [STATIC_LIB] → 
  3. Essai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonRhi                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 2 source file(s)
✓   [1/2] Compiled: Inutile.cpp
✓   [2/2] Compiled: MonRhi.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\MonRhi.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.46s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonUtil                                                          Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: MonUtil.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\MonUtil.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.49s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Essai                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:/msys64/ucrt64/bin/ld:                                                                     ║
║ C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Obj\Debug-Windows\Essai\src_Essai_main ║
║ .obj: in function `main':                                                                    ║
║ C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\src\Essai/main.cpp:5:(.text+0x17): undefined ║
║ reference to `PrintUtil()'                                                                   ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocation)            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\Essai\Essai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.53s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  2/3
Failed:         1
Errors:         2
Time:           1.49s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ Essai

On obtient bien l'erreur mentionné dans le cours **undefined reference to PrintUtil()** qui montre que le lieur ne sait pas quoi chercher pour la fonction `PrintUtil`


### 'MonUtil' ajouté à Links

with project("Essai"):
              consoleapp()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/Essai/**.cpp"])
              includedirs(["src"])
              libdirs(["%{wks.location}/Build/Lib/"
                     "%{cfg.buildcfg}-%{cfg.system}"])
              links(["MonRhi", "MonUtil"])
              objdir("%{wks.location}/Build/Obj/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
              targetdir("%{wks.location}/Build/Bin/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

  
PS C:\dane\ecole\Teguis\exercices\ani-4077\DaneRhi> jenga build 

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

Build Order (3 projects):
  1. MonRhi [STATIC_LIB] → 
  2. MonUtil [STATIC_LIB] → 
  3. Essai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonRhi                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 2 source file(s)
✓ All files up to date

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.02s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonUtil                                                          Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓ All files up to date

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.01s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Essai                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓ All files up to date
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Essai\Essai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.16s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  3/3
Time:           0.21s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════


Cette fois, la compilation est un succès, le linkage s'est bien passé. On note d'ailleurs que l'operation a très rapide (**0.21s**) car les fichiers avaient deja été compilés lors de la precedente tentative bien que soldée par un echec à cause du linkage.

### Ordre de Links inversé

with project("Essai"):
              consoleapp()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/Essai/**.cpp"])
              includedirs(["src"])
              libdirs(["%{wks.location}/Build/Lib/"
                     "%{cfg.buildcfg}-%{cfg.system}"])
              links(["MonUtil", "MonRhi"])
              objdir("%{wks.location}/Build/Obj/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
              targetdir("%{wks.location}/Build/Bin/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

Jai ensuite lancé un `jenga rebuild`

PS C:\dane\ecole\Teguis\exercices\ani-4077\DaneRhi> jenga rebuild

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

Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Obj\Debug-Windows\MonRhi\src_MonRhi_Inutile.obj
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Obj\Debug-Windows\MonRhi\src_MonRhi_MonRhi.obj
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Lib\Debug-Windows\MonRhi.lib
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Lib\Debug-Windows\MonUtil.lib
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Obj\Debug-Windows\MonUtil\src_MonUtil_MonUtil.obj
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Obj\Debug-Windows\Essai\src_Essai_main.obj
Removed C:\dane\ecole\Teguis\Exercices\ani-4077\DaneRHI\Build\Bin\Debug-Windows\Essai\Essai.exe
Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (3 projects):
  1. MonRhi [STATIC_LIB] → 
  2. MonUtil [STATIC_LIB] → 
  3. Essai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonRhi                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 2 source file(s)
✓   [1/2] Compiled: Inutile.cpp
✓   [2/2] Compiled: MonRhi.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\MonRhi.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.64s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonUtil                                                          Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: MonUtil.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\MonUtil.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.40s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Essai                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Essai\Essai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.49s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  3/3
Time:           1.53s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

Là encore la compilation est un succes . Ce qui n'est pas etonnant etant donné qu'on a constaté à l"exercice 3 que le link `MonRhi` n'est de toute façon pas indispensable ici. Je me demande d'ailleurs pourquoi l'un crée une erreur cassante et pas lautre. Pour aller plus loin ce serait peut etre interessant de créer encore un projet dont `MonUtil` depend et d''inverser encore l'ordre de linkage pour voir ce qui se passe

### Conclusion globale

Ces expériences montrent concrètement le rôle des dépendances et du linkage entre plusieurs projets C++.

Avec l'ajout de `MonUtil`, on constate d'abord que le fait que la bibliothèque soit bien compilée et présente dans le workspace ne suffit pas à rendre ses fonctions disponibles à `Essai`. Lorsque `Essai` utilise directement `PrintUtil()` sans que `MonUtil` soit présente dans `links`, la compilation de `main.cpp` réussit, mais le linkage échoue avec une erreur `undefined reference to 'PrintUtil()'`. L'ajout de `MonUtil` dans `links` permet ensuite de résoudre cette référence et de construire l'exécutable.

Le test avec les deux ordres de `links` montre ensuite que, sur la machine utilisée avec la toolchain `clang-mingw`, les deux ordres testés permettent ici d'obtenir un build réussi. L'ordre `["MonRhi", "MonUtil"]` comme l'ordre `["MonUtil", "MonRhi"]` n'a donc pas provoqué d'échec dans cette expérience.

On retient ainsi que le système de build peut construire les trois projets dans le bon ordre, mais que cela ne signifie pas automatiquement que toutes les bibliothèques sont disponibles au moment du linkage de `Essai`. Une bibliothèque dont les symboles sont utilisés doit être prise en compte par le linkage. Dans notre expérience, `MonUtil` devait donc être ajoutée à `links` dès lors que `Essai` appelait directement `PrintUtil()`.

Enfin, cette expérience montre l'intérêt de distinguer la compilation de l'édition de liens : ici, les fichiers sources sont correctement compilés, mais c'est au moment de la résolution des références entre bibliothèques que l'absence de `MonUtil` provoque l'échec.