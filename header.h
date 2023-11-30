#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#endif // HEADER_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int valeur;
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    float temps;
    int couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;

/* Graphe pour les usines*/
typedef struct Usine{
    int num_Usine;
    int nb_Usines;
    pSommet* pSommet;
    struct Usine* Usine_suivante;
} Usine;

///Ajout des fonction pour les utiliser dans les autres fichier.

int taille_fichier(char* nomfichier);
Graphe * exclusions(Graphe* g);
Graphe * precedences(Graphe* g);
int obtenirIndiceSommet1(Graphe *graphe, int valeurSommet);
Graphe * lire_graphe1(char * nomFichier);
void graphe_afficher1(Graphe* graphe);
void afficher_successeurs1(Graphe* graphe, int sommet);
int* BFS(Graphe* g, int sommet_initial, int couleur);
float temps_cycle();
Usine * ws_precedences(Graphe* g, float temps_cycle);
int Yacine();



