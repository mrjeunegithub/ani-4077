### Exercice 2 Le workspace retiré

J'ai commenté la ligne "with workspace" puis arrangé le code pour qu'il reste valide syntaxiquement. 

#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from Jenga import *

#with workspace("MonRhiWks", location="."):
configurations(["Debug", "Release"])

# La bibliotheque : du code compile, sans main.
with project("MonRhi"):
       staticlib()
       language("C++")
       cppdialect("C++17")
       location(".")
       files(["src/MonRhi/**.cpp"])
       includedirs(["src"])
       objdir("%{wks.location}/Build/Obj/"
              "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
       targetdir("%{wks.location}/Build/Lib/"
              "%{cfg.buildcfg}-%{cfg.system}")

# Le programme qui s'en sert.
with project("Essai"):
       consoleapp()
       language("C++")
       cppdialect("C++17")
       location(".")
       files(["src/Essai/**.cpp"])
       includedirs(["src"])
       libdirs(["%{wks.location}/Build/Lib/"
              "%{cfg.buildcfg}-%{cfg.system}"])
       links(["MonRhi"])
       objdir("%{wks.location}/Build/Obj/"
              "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
       targetdir("%{wks.location}/Build/Bin/"
              "%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")


J'ai en ensuite tapé les commandes **jenga info** et **jenga build** qui m'ont toutes les deux renvoyés le meme retour 

PS C:\dane\ecole\Teguis\exercices\DaneRhi> jenga info 

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

## No .jenga workspace file found.

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

## No .jenga workspace file found.


Cela nous montre que jenga a besoin d'un workspace, un cadre pour travailler. On peut faire l'analogie avec un professeur et ses élèves: sans une salle de classe, il ne peut pas les tenir. Le professeur représente ici jenga, les éleves sont les projets et la salle de classe représente le workspace.

Ceci etant dit, je tiens à noter que le résultat de cet exercice contredit le cours qui dit ceci **Un project sans workspace autour ne produit rien, sans le dire. Le fichier est du Python valide, il s'exécute, et vous lisez Projects Built: 0/0.** 
