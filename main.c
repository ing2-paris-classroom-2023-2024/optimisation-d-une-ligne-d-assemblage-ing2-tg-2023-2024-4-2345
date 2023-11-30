#include "header.h"

int main() {



    Graphe * g_exclusions;
    g_exclusions = exclusions(g_exclusions);

    //// 2.1 - 2 Graphe de precedences
    Yacine();



    //on suprime la mémoire allouée dynamiquement
    for (int i = 0; i < g_exclusions->ordre; ++i) {
        free(g_exclusions->pSommet[i]->arc);
        free(g_exclusions->pSommet[i]);
    }
    free(g_exclusions->pSommet);
    free(g_exclusions);

    return 0;
}