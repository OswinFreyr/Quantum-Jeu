#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Types_structures.h"


//Sous programme permettant d'initialiser les données d'un joueur et de lui attribuer une couleur
void Initialisation_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    tab_Joueurs[NbJ].Cpt_Domination = 1;
    tab_Joueurs[NbJ].Cpt_Recherche = 1;
    tab_Joueurs[NbJ].Nb_cubes_Quantum = 5;
    tab_Joueurs[NbJ].Nb_Vaisseaux_Casse = 0;
    if (NbJ == 0)
        tab_Joueurs[NbJ].Couleur = 11;
    if (NbJ == 1)
        tab_Joueurs[NbJ].Couleur = 12;
    if (NbJ == 2)
        tab_Joueurs[NbJ].Couleur = 10;
    if (NbJ == 3)
        tab_Joueurs[NbJ].Couleur = 14;
}


//Sous programme permettant d'initialiser les données de tous les joueurs
void Initialisation_Joueurs (S_Joueur tab_Joueurs[], int NbJ)
{
    int i;
    for(i = 0; i < NbJ; i++)
    {
        Initialisation_Joueur(tab_Joueurs, i);
    }
}


//Sous programme permettant de créer le plateau de jeu (avec cases vides et valeurs des planètes affichées)
void Initialisation_Plateau (S_Case tab_Plateau[9][9], int NbJ)
{
    int i; int j; int k; int l;
    if (NbJ == 2)
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                tab_Plateau[i][j].Valeur = 0;
                for(k = 0; k < 4; k++)
                {
                    tab_Plateau[i][j].Cubes_Quantum[k] = 0;
                    tab_Plateau[i][j].Nb_Cubes_Quantum = 0;
                    tab_Plateau[i][j].Couleur = 15;
                }

            }
        }
        tab_Plateau[1][1].Valeur = 7; tab_Plateau[4][1].Valeur = 7; tab_Plateau[7][1].Valeur = 7; tab_Plateau[1][4].Valeur = 7; tab_Plateau[1][7].Valeur = 7; tab_Plateau[4][7].Valeur = 7; tab_Plateau[7][7].Valeur = 7;
        tab_Plateau[4][4].Valeur = 8; tab_Plateau[7][4].Valeur = 8;
    }
    if (NbJ == 3)
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                tab_Plateau[i][j].Valeur = 0;
                for(k = 0; k < 4; k++)
                {
                    tab_Plateau[i][j].Cubes_Quantum[k] = 0;
                    tab_Plateau[i][j].Nb_Cubes_Quantum = 0;
                    tab_Plateau[i][j].Couleur = 15;
                }
            }
        }
        tab_Plateau[1][1].Valeur = 7; tab_Plateau[1][7].Valeur = 7; tab_Plateau[7][4].Valeur = 7;
        tab_Plateau[4][1].Valeur = 8; tab_Plateau[7][1].Valeur = 8; tab_Plateau[1][4].Valeur = 8; tab_Plateau[4][7].Valeur = 8; tab_Plateau[7][7].Valeur = 8;
        tab_Plateau[4][4].Valeur = 9;
    }
    if (NbJ == 4)
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                tab_Plateau[i][j].Valeur = 0;
                for(k = 0; k < 4; k++)
                {
                    tab_Plateau[i][j].Cubes_Quantum[k] = 0;
                    tab_Plateau[i][j].Nb_Cubes_Quantum = 0;
                    tab_Plateau[i][j].Couleur = 15;
                }
            }
        }
        tab_Plateau[1][1].Valeur = 8; tab_Plateau[4][1].Valeur = 8; tab_Plateau[7][4].Valeur = 8; tab_Plateau[1][7].Valeur = 8; tab_Plateau[4][7].Valeur = 8;
        tab_Plateau[7][1].Valeur = 9; tab_Plateau[1][4].Valeur = 9; tab_Plateau[7][7].Valeur = 9;
        tab_Plateau[4][4].Valeur = 10;
    }
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            for(k = 0; k < 4; k++)
            {
                for(l = 0; l < 3; l++)
                {
                    tab_Plateau[i][j].Num_Vaisseaux[k][l] = 0;
                }
            }
        }
    }
}
