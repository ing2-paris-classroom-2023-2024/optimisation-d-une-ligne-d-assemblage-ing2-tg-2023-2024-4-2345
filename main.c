#include "header.h"

/// Fonction qui renvoi le nombre de ligne d'un fichier .txt
int taille_fichier(char* nomfichier){
    FILE * f = fopen(nomfichier,"r") ;
    int nbLignes = 1;
    char caractere;

    if (f == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    //On regarde chaque caractère et si il y a un \n, on augmante me nombre de lignes
    while ((caractere = fgetc(f)) != EOF) {
        if (caractere == '\n') {
            nbLignes++;
        }
    }

    fclose(f);
    return nbLignes;
}

int main() {
    int nbLignes_exclusions = taille_fichier("../exclusions.txt");
    int nbLignes_operations = taille_fichier("../operations.txt");
    int nbLignes_temps_cycle = taille_fichier("../temps_cycle.txt");
    int nbLignes_precedences = taille_fichier("../precedences.txt");

    return 0;
}
