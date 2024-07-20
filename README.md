## Pile (Stack) en C++

Ce code implémente une structure de données de type pile (stack) générique en C++. 

### Description

La classe `stack` utilise un tableau dynamique pour stocker les éléments. Elle offre les fonctionnalités suivantes :

- Constructeur par défaut et constructeur avec taille spécifiée.
- Accesseurs pour obtenir :
    - Le pointeur de base de la pile (`getBP`).
    - Une copie de l'élément au sommet de la pile (`top`).
    - Le pointeur du sommet de la pile (`getSP`).
- Méthodes pour :
    - Empiler un élément (`push`).
    - Dépiler un élément (`pop`).
    - Définir une nouvelle base pour la pile (`setBP`).
    - Libérer la mémoire allouée (`free`).

### Fonctionnement

- La pile est implémentée à l'aide d'un tableau dynamique `stk`.
- Les pointeurs `BP` et `SP` suivent respectivement la base et le sommet de la pile.
- La méthode `resize()` double la taille de la pile lorsque nécessaire.

### Utilisation

```cpp
#include "stack.h" // Inclure le fichier d'en-tête

int main() {
    // Créer une pile d'entiers de taille 10
    stack<int> maPile(10);

    // Empiler des éléments
    maPile.push(10);
    maPile.push(20);

    // Afficher l'élément au sommet
    cout << "Sommet: " << maPile.top() << endl;

    // Dépiler un élément
    maPile.pop();

    // Libérer la mémoire
    maPile.free();

    return 0;
}
```

### Remarques

- La classe utilise `realloc()` pour redimensionner la pile, ce qui peut être coûteux en termes de performances.
- Il est important d'appeler la méthode `free()` pour libérer la mémoire allouée lorsque la pile n'est plus utilisée.

### Améliorations possibles

- Implémenter un itérateur pour parcourir les éléments de la pile.
- Ajouter des méthodes pour vérifier si la pile est vide ou pleine.
- Utiliser une autre structure de données, comme une liste chaînée, pour une meilleure efficacité lors du redimensionnement. 
