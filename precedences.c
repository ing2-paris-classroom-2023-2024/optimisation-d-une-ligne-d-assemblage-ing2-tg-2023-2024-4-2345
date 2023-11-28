
#include "header.h"
void renseigner_temps(Graphe * g) {
    FILE *ifs = fopen("../operations.txt", "r");
    int indice, sommet;
    float temps;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    //Recuperer les donnees de temps par sommet
    for (int i=0; i<g->ordre-1; i++) {
        fscanf(ifs, "%d %f", &sommet, &temps);
        indice = obtenirIndiceSommet(g, sommet);
        g->pSommet[indice]->temps = temps;
    }
    fclose(ifs);
}

Graphe * precedences(Graphe* g){

    g = lire_graphe("../precedences.txt");
    renseigner_temps(g);
    //ColorisationNaive(g);
    /// afficher le graphe
    graphe_afficher(g);

    return g;
}//
// Created by yacin on 28/11/2023.
//
