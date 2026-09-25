## Exercice 5 Debug contre release mesures

J'ai ajouté une fonction for dans `Essai/main.cpp` qui somme les entiers jusqu'à cent millions

#include "MonRhi/MonRhi.h"

int main(){
    long long somme = 0;
    for(long long i=0; i<1000000000; i++){
        somme += i;
    }
    std::cout<<somme<<std::endl;
    return 0;
}

j'ai noté les temps construction et d'execution des deux configurations Debug et Release

### Debug

Compilation : **1.01s**
Execution : **75.48s**

## Release

Compilation : **1.10s**
Execution : **75.49**

On constate que la compilation en release prend un peu plus de temps. La raison est que des optimisations sont faites pour la config Release.
Pour ce qui est de lexécution, les temps sont similaires et même, le temps de release est legerement plus long d'un centième de seconde. Ce qui est surprenant vu qu'on s'attendrait à une exécution rapide en raison des optimisations. Et pourtant, dans le cas precis dune longue boucle comme ici, cette optimisation n'est pas approprié et peut meme etre plus lente parce que le compilateur duplique le corps de la boucle ce qui fait grossir le code machine exessivement.