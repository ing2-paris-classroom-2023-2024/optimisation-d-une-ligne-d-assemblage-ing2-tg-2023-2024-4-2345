//
// Created by farhan on 15/10/2023.
//Uniquement les fonctions permettant l'algorithme kruskal et prim 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // Pour INT_MAX
#include "header.h"

// Fonction de comparaison pour le tri des aretes par poids (Kruskal)
int compareKruskal(const void *a, const void *b) {
    return ((AreteKruskal *)a)->poids - ((AreteKruskal *)b)->poids;
}

// Fonction de comparaison pour le tri des aretes par poids (Prim)
int compareAretePrim(const void *a, const void *b) {
    return ((AretePrim *)a)->poids - ((AretePrim *)b)->poids;
}

// Fonction pour charger le graphe a partir d'un fichier texte
Graphe* chargerGrapheDepuisFichier(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    int numSommets, numAretes;
    fscanf(fichier, "%d", &numSommets);

    Graphe *graphe = (Graphe *)malloc(sizeof(Graphe));
    graphe->numSommets = numSommets;

    // Creez un tableau de sommets correspondant aux "idX" dans votre fichier
    char identifiantsSommets[numSommets][5];
    char nomsSommets[numSommets][20]; // Tableau pour stocker les noms associes

    for (int i = 0; i < numSommets; i++) {
        fscanf(fichier, "%s", identifiantsSommets[i]);
        snprintf(nomsSommets[i], sizeof(nomsSommets[i]), "sommet %d", i); // Associez "idX" a "sommet X"
    }

    fscanf(fichier, "%d", &numAretes);
    graphe->numAretes = numAretes;

    graphe->aretes = (AretePrim *)malloc(numAretes * sizeof(AretePrim));

    for (int i = 0; i < numAretes; i++) {
        char source[5], destination[5];
        int poids;
        fscanf(fichier, "%s %s %d", source, destination, &poids);

        // Recherchez les numeros de sommet correspondant aux "idX"
        int sommet1 = -1, sommet2 = -1;
        for (int j = 0; j < numSommets; j++) {
            if (strcmp(identifiantsSommets[j], source) == 0) {
                sommet1 = j;
            }
            if (strcmp(identifiantsSommets[j], destination) == 0) {
                sommet2 = j;
            }
        }

        // Si les sommets correspondants sont trouves, enregistrez l'arete dans la structure AretePrim
        if (sommet1 != -1 && sommet2 != -1) {
            graphe->aretes[i].sommet1 = sommet1;
            graphe->aretes[i].sommet2 = sommet2;
            graphe->aretes[i].poids = poids;
        }
    }

    fclose(fichier);
    return graphe;
}

// Fonction pour trouver la racine d'un ensemble disjoint
int ChercherEnsemble(EnsembleDisjoint *ensembles, int index) {
    if (ensembles[index].parent != index) {
        ensembles[index].parent = ChercherEnsemble(ensembles, ensembles[index].parent);
    }
    return ensembles[index].parent;
}

// Fonction pour effectuer l'union de deux ensembles
void Assembler(EnsembleDisjoint *ensembles, int a, int b) {
    int racineA = ChercherEnsemble(ensembles, a);
    int racineB = ChercherEnsemble(ensembles, b);
    if (racineA != racineB) {
        ensembles[racineA].parent = racineB;
    }
}

// Fonction pour l'algorithme de Kruskal
void kruskal(Graphe *graphe, char nomsSommets[][20]) {
    int numSommets = graphe->numSommets;
    AretePrim *aretes = graphe->aretes;

    // Tri des aretes par poids
    qsort(aretes, graphe->numAretes, sizeof(AretePrim), compareAretePrim);

    EnsembleDisjoint *ensembles = (EnsembleDisjoint *)malloc(numSommets * sizeof(EnsembleDisjoint));

    for (int i = 0; i < numSommets; i++) {
        ensembles[i].sommet = i;
        ensembles[i].parent = i;
    }

    printf("Arbre couvrant de poids minimal (Kruskal) :\n");

    int poidsARM = 0;
    // Dans la fonction kruskal, utilisez la structure AretePrim
    for (int i = 0; i < graphe->numAretes; i++) {
        AretePrim arete = aretes[i];
        int racineSommet1 = ChercherEnsemble(ensembles, arete.sommet1);
        int racineSommet2 = ChercherEnsemble(ensembles, arete.sommet2);

        if (racineSommet1 != racineSommet2) {
            printf("%s <--[%d]--> %s\n", nomsSommets[arete.sommet1], arete.poids, nomsSommets[arete.sommet2]);
            poidsARM += arete.poids;
            Assembler(ensembles, racineSommet1, racineSommet2);
        }
    }

    printf("Poids total de l'arbre de recouvrement minimal (Kruskal) : %d\n\n\n", poidsARM);
    free(ensembles);
}

