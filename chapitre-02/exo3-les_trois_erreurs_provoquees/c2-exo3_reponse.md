# C2 — Exercice 3

## 1. Retrait de `includedirs`

with project("Essai"):
              consoleapp()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/Essai/\*\*.cpp"])
              #includedirs(["src"])
              libdirs(["%{wks.location}/Build/Lib/"
                     "%{cfg.buildcfg}-%{cfg.system}"])
              links(["MonRhi"])
              objdir("%{wks.location}/Build/Obj/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
              targetdir("%{wks.location}/Build/Bin/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

### Message obtenu

PS C:\dane\ecole\Teguis\Exercices\DaneRhi> jenga build

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
✓ All files up to date

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.00s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Essai                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:\dane\ecole\Teguis\Exercices\DaneRHI\src\Essai\main.cpp:1:10: fatal error:                 ║
║ 'MonRhi/MonRhi.h' file not found                                                             ║
║     1 | #include "MonRhi/MonRhi.h"                                                           ║
║       |          ^~~~~~~~~~~~~~~~~                                                           ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\dane\ecole\Teguis\Exercices\DaneRHI\src\Essai\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.10s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/2
Failed:         1
Errors:         2
Time:           0.10s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ Essai

### Outil qui a parlé

**Le compilateur Clang**, appelé par Jenga.

### Conclusion

Le retrait de `includedirs` empêche le compilateur de trouver le fichier d'en-tête `MonRhi/MonRhi.h`. Cela montre que `includedirs` définit les chemins de recherche des fichiers inclus pendant la compilation. L'erreur apparaît donc avant le linkage.

---

## 2. Retrait de `libdirs`

J'ai commenté `libdirs` puis lancé un **rebuild**, afin de supprimer les anciens fichiers compilés et vérifier que le résultat ne venait pas d'une construction précédente. Et ce parce que j'ai d'abord lancé un simple jenga build et le resultat etait un succès

with project("Essai"):
              consoleapp()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/Essai/\*\*.cpp"])
              includedirs(["src"])
              #libdirs(["%{wks.location}/Build/Lib/"
              #       "%{cfg.buildcfg}-%{cfg.system}"])
              links(["MonRhi"])
              objdir("%{wks.location}/Build/Obj/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
              targetdir("%{wks.location}/Build/Bin/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

### Message obtenu

PS C:\dane\ecole\Teguis\Exercices\DaneRhi> jenga rebuild

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

Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Obj\Debug-Windows\MonRhi\src_MonRhi_MonRhi.obj
Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Lib\Debug-Windows\MonRhi.lib
Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Obj\Debug-Windows\Essai\src_Essai_main.obj
Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Bin\Debug-Windows\Essai\Essai.exe
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
│  ✓ Build Successful                                                             Time: 0.65s  │
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
║ C:/msys64/ucrt64/bin/ld: cannot find -lMonRhi: No such file or directory                     ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocation)            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\Essai\Essai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.48s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/2
Failed:         1
Errors:         1
Time:           1.13s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ Essai


### Outil qui a parlé

**Le linker GNU ld**, appelé dans la chaîne Clang++/MinGW.

### Conclusion

Le retrait de `libdirs` n'empêche pas la compilation de `main.cpp`, mais le linker ne trouve plus la bibliothèque `MonRhi`. Cela montre que `libdirs` indique les répertoires dans lesquels le linker recherche les bibliothèques nécessaires à l'édition des liens.

## 3. Retrait de `links`

with project("Essai"):
              consoleapp()
              language("C++")
              cppdialect("C++17")
              location(".")
              files(["src/Essai/\*\*.cpp"])
              includedirs(["src"])
              libdirs(["%{wks.location}/Build/Lib/"
                     "%{cfg.buildcfg}-%{cfg.system}"])
              #links(["MonRhi"])
              objdir("%{wks.location}/Build/Obj/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
              targetdir("%{wks.location}/Build/Bin/"
                     "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")


### Message obtenu

PS C:\dane\ecole\Teguis\Exercices\DaneRhi> jenga rebuild

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

Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Obj\Debug-Windows\MonRhi\src_MonRhi_MonRhi.obj
Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Lib\Debug-Windows\MonRhi.lib
Removed C:\dane\ecole\Teguis\Exercices\DaneRHI\Build\Obj\Debug-Windows\Essai\src_Essai_main.obj
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
│  ✓ Build Successful                                                             Time: 0.43s  │
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
Projects Built:  2/2
Time:           0.91s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

### Outil qui a parlé

**Jenga**, qui a affiché le résultat global de la construction. La compilation et le linkage ont été réalisés par Clang/MinGW, mais aucun outil n'a signalé d'erreur.

### Conclusion

Dans cette expérience, retirer `links` n'a pas provoqué d'erreur. Cela montre que le projet pouvait encore être construit sans cette directive, probablement parce que les symboles utilisés ne nécessitaient pas effectivement de résolution dans `MonRhi`, ou parce qu'une autre configuration permettait encore la construction.

Cela ne signifie pas que `links` est inutile en général : si le programme utilisait des fonctions définies uniquement dans une bibliothèque non liée, le linker pourrait signaler des références non définies.

## Tableau récapitulatif

| Ligne retirée | Message obtenu | Outil qui a parlé |

| `includedirs` | `'MonRhi/MonRhi.h' file not found` | Compilateur Clang |
| `libdirs` | `cannot find -lMonRhi: No such file or directory` | Linker GNU `ld` |
| `links` | `Build Successful` | Jenga, avec Clang/MinGW en arrière-plan |

## Conclusion générale

Cette expérience montre que les trois directives interviennent à des étapes différentes :

- `includedirs` agit lors de la **compilation**, pour trouver les fichiers d'en-tête.
- `libdirs` agit lors du **linkage**, pour trouver les fichiers de bibliothèque.
- `links` indique les bibliothèques que le linker doit effectivement utiliser.

Le tableau permet donc de distinguer rapidement une erreur de compilation d'une erreur d'édition des liens et d'identifier la directive responsable.
