//Coloration d'un graphe en utilisant l'algo de Welsh et Powell

#include <stdio.h>
#include <stdlib.h>

// Nombre maximal de sommets dans le graphe
#define MAX_VERTICES 100

// Structure pour représenter un graphe
typedef struct {
    int numVertices;
    int **adjMatrix;
} Graph;

// Fonction pour créer un graphe avec un nombre spécifié de sommets
Graph *createGraph(int numVertices) {
    int i, j;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Allocation de la matrice d'adjacence
    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Fonction pour ajouter une arête entre deux sommets du graphe
void addEdge(Graph *graph, int start, int end) {
    graph->adjMatrix[start][end] = 1;
    graph->adjMatrix[end][start] = 1;
}

// Fonction pour colorier le graphe en utilisant l'algorithme de Welsh-Powell
void colorGraph(Graph *graph) {
    int numVertices = graph->numVertices;
    int *color = (int *)malloc(numVertices * sizeof(int));

    // Initialiser toutes les couleurs à -1 (non attribuées)
    for (int i = 0; i < numVertices; i++) {
        color[i] = -1;
    }

    // La couleur actuelle
    int currentColor = 0;

    // Colorier le premier sommet avec la couleur 0
    color[0] = currentColor;

    // Colorier les autres sommets
    for (int i = 1; i < numVertices; i++) {
        int j;
        for (j = 0; j < numVertices; j++) {
            // Si le sommet n'est pas adjacent à i et n'a pas déjà une couleur attribuée
            if (graph->adjMatrix[i][j] == 0 && color[j] == -1) {
                color[j] = currentColor;
            }
        }
        // Passer à la prochaine couleur
        currentColor++;
    }

    // Afficher les couleurs attribuées à chaque sommet
    printf("Coloration du graphe :\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Sommet %d : Couleur %d\n", i, color[i]);
    }

    free(color);
}

// Fonction principale
int main() {
    // Créer un graphe avec 5 sommets
    Graph *graph = createGraph(5);

    // Ajouter des arêtes au graphe
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Colorier le graphe
    colorGraph(graph);

    return 0;
}
