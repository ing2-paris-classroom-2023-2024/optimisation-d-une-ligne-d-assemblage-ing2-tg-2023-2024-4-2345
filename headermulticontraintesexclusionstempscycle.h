typedef struct Arc {
    int sommet;
    struct Arc* arc_suivant;
} Arc, *pArc;

typedef struct Sommet {
    int valeur;
    int couleur;
    pArc arc;
} Sommet, *pSommet;

typedef struct Graphe {
    int ordre;
    int taille;
    int orientation;
    pSommet pSommet[MAX_STATIONS];
} Graphe;
