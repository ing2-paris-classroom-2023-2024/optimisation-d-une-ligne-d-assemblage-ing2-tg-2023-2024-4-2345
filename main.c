#include "header.h"


int main() {

    Graphe * g_exclusions;

    g_exclusions = exclusions(g_exclusions);



   // repartition_2_1(g_exclusions);

    //on suprime la mémoire alloué dinamiquement
    for (int i = 0; i < g_exclusions->ordre; ++i) {
        free(g_exclusions->pSommet[i]->arc);
        free(g_exclusions->pSommet[i]);

    }
    free(g_exclusions->pSommet);
    free(g_exclusions);


    return 0;
}
