#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Types_structures.h"
#include "Outils.h"
#include "Initialisation.h"
#include "Affichage.h"
#include "Start_Vaisseaux.h"
#include "Premier_Joueur.h"
#include "Deploiement_Vaisseaux.h"


//Sous programme permettant aux joueurs de déployer leurs vaisseaux en commençant par le premier joueur
void Deploiement_Vaisseaux (S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1)
{
    Choix_Planetes(tab_Joueurs, tab_Plateau, NbJ, J1);
    Choix_Positions(tab_Joueurs, tab_Plateau, NbJ, J1);
}


//Sous programme permettant aux joueurs de choisir leur planète de départ sur le plateau de jeu
void Choix_Planetes (S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1)
{
    int Choix = 0;
    int tab_Planete_Depart[4] = {0,0,0,0};
    for (int i = 0; i < NbJ; i++)
    {
        printf("\nLe joueur %d choisit sa planète de départ\n\n", i + 1);
        if (NbJ == 2)
        {
            printf("Quelle planète de départ choisissez vous ? (1.Bas Gauche coordonnées L8/C2   2. Haut Droite coordonnées L2/C8)\n\n");
            scanf("%d", &Choix);
            while(tab_Planete_Depart[Choix-1] == 1 || Choix < 1 || Choix > 2)
            {
                printf("Choix invalide, réessayez\n");
                scanf("%d",&Choix);
            }
            printf("\n");
            tab_Planete_Depart[Choix-1] = 1;
            tab_Joueurs[(J1 + i)%NbJ].Nb_cubes_Quantum -= 1;
            if (Choix == 1)
            {
                tab_Plateau[7][1].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[7][1].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 2)
            {
                tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[1][7].Nb_Cubes_Quantum = 1;
            }
        }
        if (NbJ == 3)
        {
            printf("Quelle planète de départ choisissez vous ? (1.Haut Gauche coordonnées L2/C2   2. Haut Droite coordonnées L2/C8  3. Bas Milieu coordonnées L8/C5)\n\n");
            scanf("%d", &Choix);
            while(tab_Planete_Depart[Choix-1] == 1 || Choix < 1 || Choix > 3)
            {
                printf("Choix invalide, réessayez\n");
                scanf("%d",&Choix);
            }
            printf("\n");
            tab_Planete_Depart[Choix-1] = 1;
            tab_Joueurs[(J1 + i)%NbJ].Nb_cubes_Quantum -= 1;
            if (Choix == 1)
            {
                tab_Plateau[1][1].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[1][1].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 2)
            {
                tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[1][7].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 3)
            {
                tab_Plateau[7][4].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[7][4].Nb_Cubes_Quantum = 1;
            }
        }
        if (NbJ == 4)
        {
            printf("Quelle planète de départ choisissez vous ? (1.Haut Gauche coordonnées L2/C2   2. Haut Droite coordonnées L2/C8  3. Bas Droite coordonnées L8/C8  4. Bas Gauche coordonnées L8/C2)\n\n");
            scanf("%d", &Choix);
            while(tab_Planete_Depart[Choix-1] == 1 || Choix < 1 || Choix > 4)
            {
                printf("Choix invalide, réessayez\n");
                scanf("%d",&Choix);
            }
            printf("\n");
            tab_Planete_Depart[Choix-1] = 1;
            tab_Joueurs[(J1 + i)%NbJ].Nb_cubes_Quantum -= 1;
            if (Choix == 1)
            {
                tab_Plateau[1][1].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[1][1].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 2)
            {
                tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[1][7].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 3)
            {
                tab_Plateau[7][7].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[7][7].Nb_Cubes_Quantum = 1;
            }
            if (Choix == 4)
            {
                tab_Plateau[7][1].Cubes_Quantum[(J1 + i)%NbJ] = 1;
                tab_Plateau[7][1].Nb_Cubes_Quantum = 1;
            }
        }
    }
}


//Sous programme permettant aux joueurs de choisir les positions de départ de leurs vaisseaux suivant la planète de départ sélectionnée
void Choix_Positions (S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1)
{
    int Choix = 0;
    for (int i = 0; i < NbJ; i++)
    {
        printf("\nLe joueur %d choisit les positions de départ de ses vaisseaux\n\n", i + 1);
        int tab_Emplacement_Vaisseaux[4] = {0,0,0,0};
        if (NbJ == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("\nLe joueur %d choisit la position de départ de son vaisseau %d\n", i + 1, j + 1);
                printf("1.En haut\t 2.A droite\n 3.En bas\t 4.A gauche\n");
                scanf("%d", &Choix);
                while (tab_Emplacement_Vaisseaux[Choix-1] == 1 || Choix < 1 || Choix > 4)
                {
                     printf("Choix invalide, réessayez\n");
                     scanf("%d", &Choix);
                }
                tab_Emplacement_Vaisseaux[Choix-1] = 1;
                if (tab_Plateau[7][1].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[6][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[6][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[6][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;

                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[7][2].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][2].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][2].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[8][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[8][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[8][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[7][0].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][0].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][0].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[0][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[0][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[0][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[1][8].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][8].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][8].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[2][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[2][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[2][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[1][6].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][6].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][6].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
            }
        }
        if (NbJ == 3)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("\nLe joueur %d choisit la position de départ de son vaisseau %d\n", i + 1, j + 1);
                printf("1.En haut\t 2.A droite\n 3.En bas\t 4.A gauche\n");
                scanf("%d", &Choix);
                while (tab_Emplacement_Vaisseaux[Choix-1] == 1 || Choix < 1 || Choix > 4)
                {
                     printf("Choix invalide, réessayez\n");
                     scanf("%d", &Choix);
                }
                tab_Emplacement_Vaisseaux[Choix-1] = 1;
                if (tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[0][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[0][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[0][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;

                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[1][8].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][8].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][8].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[2][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[2][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[2][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[1][6].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][6].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][6].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[1][1].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[0][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[0][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[0][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[1][2].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][2].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][2].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[2][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[2][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[2][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[1][0].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][0].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][0].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[7][4].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[6][4].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[6][4].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[6][4].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[7][5].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][5].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][5].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[8][4].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[8][4].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[8][4].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[7][3].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][3].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][3].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
            }
        }
        if (NbJ == 4)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("\nLe joueur %d choisit la position de départ de son vaisseau %d\n", i + 1, j + 1);
                printf("1.En haut\t 2.A droite\n 3.En bas\t 4.A gauche\n");
                scanf("%d", &Choix);
                while (tab_Emplacement_Vaisseaux[Choix-1] == 1 || Choix < 1 || Choix > 4)
                {
                     printf("Choix invalide, réessayez\n");
                     scanf("%d", &Choix);
                }
                tab_Emplacement_Vaisseaux[Choix-1] = 1;
                if (tab_Plateau[7][1].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[6][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[6][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[6][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[7][2].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][2].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][2].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[8][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[8][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[8][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[7][0].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][0].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][0].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[1][1].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[0][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[0][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[0][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[1][2].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][2].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][2].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[2][1].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[2][1].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[2][1].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[1][0].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][0].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][0].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[1][7].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[0][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[0][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[0][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[1][8].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][8].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][8].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[2][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[2][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[2][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[1][6].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[1][6].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[1][6].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
                if (tab_Plateau[7][7].Cubes_Quantum[(J1 + i)%NbJ] == 1)
                {
                    if (Choix == 1)
                    {
                        tab_Plateau[6][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[6][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[6][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 2)
                    {
                        tab_Plateau[7][8].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][8].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][8].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 3)
                    {
                        tab_Plateau[8][7].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[8][7].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[8][7].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                    if (Choix == 4)
                    {
                        tab_Plateau[7][6].Valeur = tab_Joueurs[(J1 + i)%NbJ].tab_Vaisseaux[j];
                        tab_Plateau[7][6].Num_Vaisseaux[(J1 + i)%NbJ][j] = j + 1;
                        tab_Plateau[7][6].Couleur = tab_Joueurs[(J1 + i)%NbJ].Couleur;
                    }
                }
            }
        }
    }
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}
