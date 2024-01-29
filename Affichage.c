#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Types_structures.h"
#include "Initialisation.h"
#include "Affichage.h"
#include "Outils.h"


//Sous programme affichant les données d'un joueur après initialisation
void Affichage_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    printf("La valeur de votre Dé Domination est %d\n", tab_Joueurs[NbJ].Cpt_Domination);
    printf("La valeur de votre Dé Recherche est %d\n", tab_Joueurs[NbJ].Cpt_Recherche);
    printf("Vous possédez %d cubes Quantum\n", tab_Joueurs[NbJ].Nb_cubes_Quantum);
    printf("Vous avez %d Vaisseaux dans votre casse\n\n\n", tab_Joueurs[NbJ].Nb_Vaisseaux_Casse);
}


//Sous programme affichant les données de tous les joueurs après initialisation
void Affichage_Joueurs (S_Joueur tab_Joueurs[], int NbJ)
{
    int i;
    for(i = 0; i < NbJ; i++)
    {
        color(tab_Joueurs[i].Couleur,0);
        Affichage_Joueur (tab_Joueurs, i);
        color (15,0);
    }
}


//Sous programme permettant d'afficher le plateau
void Affichage_Plateau (S_Case tab_Plateau[9][9], S_Joueur tab_Joueurs[], int NbJ, int J1)
{
    color(15,0);
    int i; int j; int k;
    if (NbJ == 2 || NbJ == 3)
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
                if (tab_Plateau[i][j].Valeur > 6)
                    color (13,0);
                if (tab_Plateau[i][j].Valeur < 7 && tab_Plateau[i][j].Valeur > 0)
                {
                    for (k = 0; k < NbJ; k++)
                    {
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                    }
                }
                printf(" %d ", tab_Plateau[i][j].Valeur);
                color (15,0);
        }
        printf("\n");
    }
    if (NbJ == 4)
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                if (tab_Plateau[i][j].Valeur > 6)
                    color (13,0);
                if (tab_Plateau[i][j].Valeur < 7 && tab_Plateau[i][j].Valeur > 0)
                {
                    for (k = 0; k < NbJ; k++)
                    {
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][0] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][1] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                        if ((tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 1) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 2) || (tab_Plateau[i][j].Num_Vaisseaux[(J1 + k)%NbJ][2] == 3))
                            color(tab_Joueurs[(J1 + k)%NbJ].Couleur,0);
                    }
                }
                if (tab_Plateau[i][j].Valeur > 9)
                    printf(" %d ",tab_Plateau[i][j].Valeur);
                if (tab_Plateau[i][j].Valeur < 10)
                    printf("  %d ",tab_Plateau[i][j].Valeur);
                    color (15,0);
            }
        printf("\n");
        }
    }
    printf("\n\n");
}


