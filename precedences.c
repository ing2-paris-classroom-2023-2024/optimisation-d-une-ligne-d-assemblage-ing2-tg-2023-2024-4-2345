

#include "header.h"

float temps_cycle() {
    FILE *ifs = fopen("../temps_cycle.txt", "r");
    float temps;
    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    //Recuperer les donnees de temps cycle
    fscanf(ifs, "%f", &temps);
    return temps;
    fclose(ifs);
}

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

    g = lire_graphe1("../precedences.txt");
    renseigner_temps(g);
    //ColorisationNaive(g);
    /// afficher le graphe
    graphe_afficher1(g);

    return g;
}

Usine * ws_precedences(Graphe* g, float temps_cycle){
    int * liste;
    int i,j,k;
    float temps_c = 0;
    liste = BFS(g, 1,1);
    i=0;
    k=1;
    j= obtenirIndiceSommet1(g, 1);
    while ((liste[i] != -1) && (i < 20)){
        printf("\n\nWS %d", k);
        while (temps_c + g->pSommet[j]->temps <= temps_cycle){
            j = obtenirIndiceSommet1(g, liste[i]);
            printf("\n  %d-%.2f ", g->pSommet[j]->valeur, g->pSommet[j]->temps);
            temps_c = temps_c + g->pSommet[j]->temps;
            printf("\n temps de cycle %.2f ", temps_c);
            i++;
            j = obtenirIndiceSommet1(g, liste[i]);
        }
        temps_c = 0;
        k++;
    }
}