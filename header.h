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
    int Num_Usine;
    int Nb_Sommet;
    pSommet* pSommet;
    struct Usine* Usine_suivante;
} Usine;

///Ajout des fonction pour les utiliser dans les autres fichier.

int taille_fichier(char* nomfichier);
Graphe * exclusions(Graphe* g);
void repartition_2_1(Graphe* g);
