#include "header.h"



//Cet fonction répartie les actions dans les usines par rapport à l'exclusion.
void repartition_2_1(Graphe* g){
    Usine * U = (Usine *)malloc(sizeof(Usine));
    int utilise[g->ordre];
//Création d'un tableau vec tout les point qui vont plus tatrd être remplacé par -1 quand les points seront utilisé.
    for (int i = 0; i < g->ordre; ++i) {
        utilise[i] = g->pSommet[i]->valeur;
    }

    U->pSommet = (pSommet)malloc(taille_fichier("../operations.txt") * sizeof(struct Sommet));

    for (int i = 0; i < g->ordre; ++i) {

    }
}