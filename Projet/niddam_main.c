#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "header.h"

#define TAILLE_TAB 10

int main(int argc, char const *argv[])
{
    int matrice[TAILLE_TAB][TAILLE_TAB] = {0};
    int matrice_puissance_n[TAILLE_TAB][TAILLE_TAB] = {0};
    int PS[TAILLE_TAB] = {0};
    int LS[TAILLE_TAB] = {0};
    int DEGE[TAILLE_TAB] = {0};
    int DEGS[TAILLE_TAB] = {0};
    int circuit[TAILLE_TAB] = {0};
    int succs[TAILLE_TAB] = {0};
    int marques[TAILLE_TAB] = {0};

    int nb_som;

    PS[1] = 1;
    PS[2] = 5;
    PS[3] = 9;

    LS[1] = 2;
    LS[2] = 3;
    LS[3] = 4;
    LS[4] = 0;
    LS[5] = 2;
    LS[6] = 5;
    LS[7] = 7;
    LS[8] = 0;
    LS[9] = 8;
    LS[10] = 0;

    implementer_graphe(matrice, TAILLE_TAB);
    ajouterSomMatrice(matrice, PS, TAILLE_TAB);
    ajouterArcMatrice(matrice, LS, TAILLE_TAB);
    matriceVersPSLS(matrice, PS, LS, nb_som);
    int som1, som2;
    printf("Entrez les deux sommets séparés par un espace: ");
    scanf("%d %d", &som1, &som2);
    rechercheArcMatrice(matrice, som1, som2);
    afficherMatrice(matrice, TAILLE_TAB);
    rechercherArcLS(LS, som1, som2);
    rechercherArcPSLS(PS, LS, som1, som2);
    rechercherCircuit(LS, PS, circuit, nb_com, TAILLE_TAB);
    degresEntrantSortantPSLS(PS, LS, DEGE, DEGS);
    matricePuissanceN(matrice, matrice_puissance_n, 3, TAILLE_TAB);
    Tremaux(PS, LS, succs, marques, nb_som, 1);
    parcoursLargeur(PS, LS, succs, marques, nb_som, 1);

    return 0;
}
