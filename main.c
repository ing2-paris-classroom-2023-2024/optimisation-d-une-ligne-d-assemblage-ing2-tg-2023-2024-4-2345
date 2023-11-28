// Fonction pour obtenir l'indice du sommet dans le tableau pSommet de Graphe
#include "header.h"

int obtenirIndiceSommet(Graphe *graphe, int valeurSommet){
    int indice = -1;
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->valeur == valeurSommet) {
            indice = i;
        }
    }
    return indice;
}

/* affichage des successeurs du sommet num*/
void afficher_successeurs(Graphe* graphe, int num)
{
    int i;
    printf("\nsommet %d-%.2f \n", graphe->pSommet[num]->valeur, graphe->pSommet[num]->temps);

    pArc arc = graphe->pSommet[num]->arc;

    while(arc!=NULL)
    {
        i = obtenirIndiceSommet(graphe, arc->sommet);
        printf("%d-%.2f ",graphe->pSommet[i]->valeur, graphe->pSommet[i]->temps);
        arc = arc->arc_suivant;
    }

}

///Cette fonction remplace CreerArete car elle ne fonctionnais pas bien.
void CreerLiaison(Graphe* graphe, int s1, int s2){
    int i_s1 = -1;
    int i_s2 = -1;

    //On trouve le sommet qui a pour valeur S1 puis S2
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->valeur == s1) {
            i_s1 = i;
        }

        if (graphe->pSommet[i]->valeur == s2) {
            i_s2 = i;
        }

        // Si les deux sommets sont trouvés, on sort de la boucle
        if (i_s1 != -1 && i_s2 != -1) {
            break;
        }
    }

    // Création de la liaison
    pArc nouvelle_liaison = (pArc)malloc(sizeof(struct Arc));
    nouvelle_liaison->sommet = s2;
    nouvelle_liaison->arc_suivant = graphe->pSommet[i_s1]->arc;
    graphe->pSommet[i_s1]->arc = nouvelle_liaison;

    // Si le graphe n'est pas orienté, on crée également la liaison dans l'autre sens
    if (!graphe->orientation) {
        pArc nouvelle_liaison_inverse = (pArc)malloc(sizeof(struct Arc));
        nouvelle_liaison_inverse->sommet = s1;
        nouvelle_liaison_inverse->arc_suivant = graphe->pSommet[i_s2]->arc;
        graphe->pSommet[i_s2]->arc = nouvelle_liaison_inverse;
    }
}

// créer le graphe
///Le code a été changé de façon à régler le problème des numéro qui n'existe pas
///ou ce qui existe mais qui ont une valeur supérieur à celle de l'ordre du graphe
Graphe* CreerGraphe(int ordre, int taille, int orientation, FILE * ifs, char * nomFichier){
    Graphe * Newgraphe = (Graphe*)malloc(sizeof(Graphe));

    //on réouvre le fichier
    ifs = fopen(nomFichier,"r");

    Newgraphe->orientation = orientation;
    Newgraphe->ordre = ordre;
    Newgraphe->taille = taille;

    Newgraphe->pSommet = (pSommet)malloc(ordre * sizeof(struct Sommet));

    int s1, s2;
    int j = 0;
    int existe1, existe2;

    //On lit le fichier pour ensuite créer le sommet si il n'existe pas déjà
    for (int i = 0; i < taille; ++i){

        fscanf(ifs,"%d %d",&s1,&s2);;

        if(j == 0){
            Newgraphe->pSommet[j] = (pSommet)malloc(sizeof(struct Sommet));

            Newgraphe->pSommet[j]->valeur = s1;
            Newgraphe->pSommet[j]->arc = NULL;
            j++;

            Newgraphe->pSommet[j] = (pSommet)malloc(sizeof(struct Sommet));

            Newgraphe->pSommet[j]->valeur = s2;
            Newgraphe->pSommet[j]->arc = NULL;
            j++;
        } else{
            existe1 = 0;
            existe2 = 0;
            //on verifie si le sommet existe déja
            for (int k = 0; k < j; ++k) {
                if (Newgraphe->pSommet[k]->valeur == s1){
                    existe1 = 1;
                }
                if (Newgraphe->pSommet[k]->valeur == s2){
                    existe2 = 1;
                }
            }
            //on créer les sommets si ils n'existent pas
            if (!existe1){
                Newgraphe->pSommet[j] = (pSommet)malloc(sizeof(struct Sommet));

                Newgraphe->pSommet[j]->valeur = s1;
                Newgraphe->pSommet[j]->arc=NULL;
                j++;
            }
            if (!existe2){
                Newgraphe->pSommet[j] = (pSommet)malloc(sizeof(struct Sommet));

                Newgraphe->pSommet[j]->valeur = s2;
                Newgraphe->pSommet[j]->arc=NULL;
                j++;
            }
        }
    }
    Newgraphe->ordre = j;
    fclose(ifs);
    return Newgraphe;
}



/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fclose(ifs);

    ordre = taille_fichier("../operations.txt");
    taille = taille_fichier("../precedences.txt");
    orientation = 1;

    graphe = CreerGraphe(ordre, taille, orientation, ifs , nomFichier); // créer le graphe d'ordre sommets avec les bons numéros

    /// on réouvre le fichier car il a totalement était lus puis fermé dans la fonction CreerGraphe
    ifs = fopen(nomFichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i) {
        fscanf(ifs, "%d %d", &s1, &s2);
        CreerLiaison(graphe, s1, s2);

    }

    fclose(ifs);
    return graphe;
}

void graphe_afficher(Graphe* graphe)
{
    /*printf("graphe\n");

    if(graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("successeurs :\n");*/

    for (int i = 0; i < graphe->ordre; i++)
    {
        afficher_successeurs(graphe, i);
        printf("\n");
    }

}

int main() {

    Graphe * g_exclusions;
    Graphe * g_precedences;

    //g_exclusions = exclusions(g_exclusions);
    g_precedences = precedences(g_precedences);

    // repartition_2_1(g_exclusions);
    //repartition_2_2(g_exclusions);
    //on suprime la mémoire alloué dynamiquement
    for (int i = 0; i < g_exclusions->ordre; ++i) {
        free(g_exclusions->pSommet[i]->arc);
        free(g_exclusions->pSommet[i]);
    }
    free(g_exclusions->pSommet);
    free(g_precedences);
    for (int i = 0; i < g_precedences->ordre; ++i) {
        free(g_precedences->pSommet[i]->arc);
        free(g_precedences->pSommet[i]);
    }
    free(g_precedences->pSommet);
    free(g_precedences);
    return 0;
}

