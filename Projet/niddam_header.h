#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TAILLE_TAB 10

void implementer_graphe(int matrice[TAILLE_TAB][TAILLE_TAB], int taille_tab, int nb_som);
{
    int som, suiv;
    nb_som = 0;

    do
    {
        printf("Entrez un sommet du graphe : ");
        scanf("%d", &som);

        if (som != -1)
            do
            {
                printf("Entrez un sommet adjacent au sommet %d: ", som);
                scanf("%d", &suiv);

                if (suiv != -1)
                {
                    matrice[som][suiv] = 1;
                    nb_som++;
                }

            } while (suiv != -1);

    } while (som != -1);
}

void initialiserMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int taille)
{
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++)
            matrice[i][j] = 0;
}

void remplirMatriceAleatoirement(int matrice[TAILLE_TAB][TAILLE_TAB], int taille)
{
    /*
        fonction qui remplit la matrice aléatoirement de 0 et 1
    */
    srand(time(NULL));
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++)
            matrice[i][j] = rand() % 2;
}

void afficherMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
}

void ajouterSomMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int lien_som[TAILLE_TAB], int nb_som)
{
    int new_som = nb_som + 1;

    for (int i = 0; i < nb_som; i++)
    {
        if (lien_som[i] == 1)
            matrice[new_som][i] = 1;

        else if (lien_som[i] == -1)
            matrice[i][new_som] = 1;
    }
}

void matriceVersPSLS(int matrice[TAILLE_TAB][TAILLE_TAB], int PS[TAILLE_TAB], int LS[TAILLE_TAB], int nb_som)
{
    int c = 0;

    for (int i = 0; i < nb_som; i++)
    {
        PS[i] = c;

        for (int j = 0; j < nb_som; j++)
            if (matrice[j][i] == 1)
            {
                LS[c] = j;
                c++;
            }

        LS[c] = 0;
        c++;
    }
}

void afficherTab1D(int tab[TAILLE_TAB], int taille)
{
    for (int i = 1; i < taille; i++)
        printf("%d ", tab[i]);
}

bool rechercheArcMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int som1, int som2)
{
    if (matrice[som1 - 1][som2 - 1] == 1)
        return true;

    return false;
}

bool rechercherArcPSLS(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int som1, int som2)
{

    int k = PS[som1 - 1];
    while (LS[k] != 0)
    {
        if (LS[k] == som2)
            return true;
        k++;
    }
    return false;
}
bool rechercherArcLS(int LS[TAILLE_TAB], int som1, int som2)
{
    int c = 0, i = 0;

    while (c != som1)
    {
        if (LS[c] == 0)
            c++;
        i++;
    }

    while (LS[i] != 0 && LS[i] != som2)
        i++;

    return (LS[i] == som2);
}

void tableauSuccesseurs(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int succ[TAILLE_TAB], int som)
{
    int i = PS[som];
    int c = 0;

    while (i != 0)
    {
        succ[c] = LS[i];
        i++;
        c++;
    }
}

bool rechercherCircuit(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int circuit[TAILLE_TAB], int nb_som, int longueur_circuit)
{
    int c = 0;
    int succ[TAILLE_TAB] = {0};
    for (int i = 0; i < nb_som; i++)
    {
        tableauSuccesseurs(PS, LS, succ, i);

        for (int j = 0; j < nb_som; j++)
            if (rechercherArcLS(LS, i, succ[j]))
            {
                circuit[c] = i;
                c++;
                circuit[c] = succ[j];
                c++;
            }
    }

    if (c == longueur_circuit)
    {
        printf("Le circuit est : ");

        for (int i = 0; i < longueur_circuit; i++)
            printf("%d ", circuit[i]);

        printf("\n");
        return true;
    }

    else
        return false;
}

void degresEntrantSortantPSLS(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int degre_entrant[TAILLE_TAB], int degre_sortant[TAILLE_TAB])
{
    int i = 1;
    while (PS[i] != 0)
    {
        int j = PS[i];
        while (LS[j] != 0)
        {
            degre_sortant[i]++;
            degre_entrant[LS[j]]++;
            j++;
        }
        i++;
    }
}

void matricePuissanceN(int matrice[TAILLE_TAB][TAILLE_TAB], int matrice_puissance_n[TAILLE_TAB][TAILLE_TAB], int taille, int nbr_som, int n)
{
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++)
            matrice_puissance_n[i][j] = matrice[i][j];

    for (int i = 0; i < n; i++)
        for (int k = 0; k < taille; k++)
        {
            int a = 0, b = 0;
            for (int j = 0; j < taille; j++)
            {
                a *= matrice[k][j];
                b *= matrice_puissance_n[i][k];
            }
            matrice_puissance_n[i][k] = a || b;
        }

    printf("La matrice d'origine est : \n");
    afficherMatrice(matrice, taille);

    printf("La matrice de puissance %d est : \n", n);
    afficherMatrice(matrice_puissance_n, taille);
}

void Tremaux(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int succ[TAILLE_TAB], int marques[TAILLE_TAB], int nb_som, int som)
{
    int succs[TAILLE_TAB] = {0};
    tableauSuccesseurs(PS, LS, succs, som);

    int i = 0;
    while (succs[i] != 0)
    {
        if (marques[succs[i]] == 0)
        {
            marques[succs[i]] = 1;
            Tremaux(PS, LS, succs, marques, nb_som, succs[i]);
        }
        i++;
    }
}

void ajouterFile(int file[TAILLE_TAB], int som)
{
    int i = 0;
    while (file[i] != 0)
        i++;

    file[i] = som;
}

int getFile(int file[TAILLE_TAB])
{
    int som = file[0];
    int i = 0;
    while (file[i] != 0)
    {
        file[i] = file[i + 1];
        i++;
    }

    return som;
}

void parcoursLargeur(int PS[TAILLE_TAB], int LS[TAILLE_TAB], int succ[TAILLE_TAB], int marques[TAILLE_TAB], int nb_som, int som)
{
    int file[TAILLE_TAB] = {0};
    int marques[TAILLE_TAB] = {0};
    int succs[TAILLE_TAB] = {0};

    ajouterFile(file, som);
    marques[som] = 1;

    while (file[0] != 0)
    {
        som = getFile(file);
        printf("%d ", som);
        tableauSuccesseurs(PS, LS, succ, som);

        for (int i = 0; i < nb_som; i++)
            if (marques[succ[i]] == 0)
            {
                ajouterFile(file, succ[i]);
                marques[succ[i]] = 1;
            }
    }
}

void ajouterArcMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int som1, int som2)
{
    matrice[som1][som2] = 1;
}

void supprimerArcMatrice(int matrice[TAILLE_TAB][TAILLE_TAB], int som1, int som2)
{
    matrice[som1][som2] = 0;
}
