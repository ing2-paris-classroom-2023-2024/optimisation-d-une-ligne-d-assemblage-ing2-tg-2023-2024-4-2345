#include "header.h"
int main() {
    int nbLignes_exclusions = taille_fichier("../exclusions.txt");
    int nbLignes_operations = taille_fichier("../operations.txt");
    int nbLignes_temps_cycle = taille_fichier("../temps_cycle.txt");
    int nbLignes_precedences = taille_fichier("../precedences.txt");

    printf("%d", nbLignes_exclusions);

    return 0;
}
