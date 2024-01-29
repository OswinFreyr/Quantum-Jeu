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


//Sous programme qui déterminer qui est le premier joueur. C'est-à-dire lequel commence à choisir sa planète de départ, pose ses vaisseaux sur les positions
//orbitales, et effectuera son tour de jeu en premier
int Determination_1er_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    int i; int j; int k; int l;
    if (NbJ == 2)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        if (i > j)
        {
            printf("\nLe joueur rouge est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            return 1;
        }
        if (i < j)
        {
            printf("\nLe joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            return 0;
        }
        if (i == j)
        {
            return Egalite_2 (tab_Joueurs, i, j);
        }
    }
    if (NbJ == 3)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        k = tab_Joueurs[2].tab_Vaisseaux[0] + tab_Joueurs[2].tab_Vaisseaux[1] + tab_Joueurs[2].tab_Vaisseaux[2];
        if (j < i && j < k)
        {
            printf("\nLe joueur rouge est le joueur 1\n");
            printf("Le joueur vert est le joueur 2\n");
            printf("Le joueur bleu est le joueur 3\n");
            return 1;
        }
        if (i < j && i < k)
        {
            printf("\nLe joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
            return 0;
        }
        if (k < i && k < j)
        {
            printf("\nLe joueur vert est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur rouge est le joueur 3\n");
            return 2;
        }
        if (i == j && i < k)
            return Egalite_3 (tab_Joueurs, i, j, k);
        if (i == k && i < j)
            return Egalite_3 (tab_Joueurs, i, j, k);
        if (j == k && j < i)
            return Egalite_3 (tab_Joueurs, i, j, k);
    }
    if (NbJ == 4)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        k = tab_Joueurs[2].tab_Vaisseaux[0] + tab_Joueurs[2].tab_Vaisseaux[1] + tab_Joueurs[2].tab_Vaisseaux[2];
        l = tab_Joueurs[3].tab_Vaisseaux[0] + tab_Joueurs[3].tab_Vaisseaux[1] + tab_Joueurs[3].tab_Vaisseaux[2];
        if (i < j && i < k && i < l)
        {
            printf("\nLe joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
            printf("Le joueur jaune est le joueur 4\n");
            return 0;
        }
        if (j < i && j < k && j < l)
        {
            printf("\nLe joueur rouge est le joueur 1\n");
            printf("Le joueur vert est le joueur 2\n");
            printf("Le joueur jaune est le joueur 3\n");
            printf("Le joueur bleu est le joueur 4\n");
            return 1;
        }
        if (k < i && k < j && k < l)
        {
            printf("\nLe joueur vert est le joueur 1\n");
            printf("Le joueur jaune est le joueur 2\n");
            printf("Le joueur bleu est le joueur 3\n");
            printf("Le joueur rouge est le joueur 4\n");
            return 2;
        }
        if (l < i && l < j && l < k)
        {
            printf("\nLe joueur jaune est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur rouge est le joueur 3\n");
            printf("Le joueur vert est le joueur 4\n");
            return 3;
        }
        if (i == j && i < k && i < l)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
        if (i == k && i < j && i < l)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
        if (i == l && i < j && i < k)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
        if (j == k && j < i && j < l)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
        if (j == l && j < i && j < k)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
        if (k == l && k < i && k < i)
            return Egalite_4 (tab_Joueurs, i, j, k, l);
    }
}


//Pour une partie à 2 joueurs, sous programme permettant de déterminer le premier joueur dans le cas d'une égalité des sommes de valeur des vaisseaux
int Egalite_2 (S_Joueur tab_Joueurs[], int i, int j)
{
    int D1; int D2; int D3; int D4;
    int R1; int R2;
    do
    {
        printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
        D1 = LancerD();
        printf("%d\t", D1);
        D2 = LancerD();
        printf("%d\n\n", D2);
        D3 = LancerD();
        printf("%d\t", D3);
        D4 = LancerD();
        printf("%d\n\n", D4);
        R1 = D1 + D2;
        R2 = D3 + D4;
        printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
        printf("Le deuxieme joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R2);
        if (R1 > R2)
        {
            printf("\nLe joueur rouge est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            return 1;
        }
        else
        {
            printf("\nLe joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            return 0;
        }
    }while(R1 == R2);
}


//Pour une partie à 3 joueurs, sous programme permettant de déterminer le premier joueur dans le cas d'une égalité des sommes de valeur des vaisseaux
int Egalite_3 (S_Joueur tab_Joueurs[], int i, int j, int k)
{
    if(j == k && j < i)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur vert, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur vert est le joueur 1\n");
                printf("Le joueur bleu est le joueur 2\n");
                printf("Le joueur rouge est le joueur 3\n");
                return 2;
            }
            else
            {
                printf("\nLe joueur rouge est le joueur 1\n");
                printf("Le joueur vert est le joueur 2\n");
                printf("Le joueur bleu est le joueur 3\n");
                return 1;
            }
        }while(R1 == R2);
    }
    if(i == j && i < k)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur rouge est le joueur 1\n");
                printf("Le joueur vert est le joueur 2\n");
                printf("Le joueur bleu est le joueur 3\n");
                return 1;
            }
            else
            {
                printf("\nLe joueur bleu est le joueur 1\n");
                printf("Le joueur rouge est le joueur 2\n");
                printf("Le joueur vert est le joueur 3\n");
                return 0;
            }
        }while(R1 == R2);
    }
    if(i == k && i < j)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur vert, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur vert est le joueur 1\n");
                printf("Le joueur bleu est le joueur 2\n");
                printf("Le joueur rouge est le joueur 3\n");
                return 2;
            }
            else
            {
                printf("\nLe joueur bleu est le joueur 1\n");
                printf("Le joueur rouge est le joueur 2\n");
                printf("Le joueur vert est le joueur 3\n");
                return 0;
            }
        }while(R1 == R2);
    }
}


//Pour une partie à 4 joueurs, sous programme permettant de déterminer le premier joueur dans le cas d'une égalité des sommes de valeur des vaisseaux
int Egalite_4 (S_Joueur tab_Joueurs[], int i, int j, int k, int l)
{
    if(j == k && j < i && j < l)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur vert, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur vert est le joueur 1\n");
                printf("Le joueur jaune est le joueur 2\n");
                printf("Le joueur bleu est le joueur 3\n");
                printf("Le joueur rouge est le joueur 4\n");
                return 2;
            }
            else
            {
                printf("\nLe joueur rouge est le joueur 1\n");
                printf("Le joueur vert est le joueur 2\n");
                printf("Le joueur jaune est le joueur 3\n");
                printf("Le joueur bleu est le joueur 4\n");
                return 1;
            }
        }while(R1 == R2);
    }
    if(i == l && i < j && i < k)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur jaune, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur jaune est le joueur 1\n");
                printf("Le joueur bleu est le joueur 2\n");
                printf("Le joueur rouge est le joueur 3\n");
                printf("Le joueur vert est le joueur 4\n");
                return 3;
            }
            else
            {
                printf("\nLe joueur bleu est le joueur 1\n");
                printf("Le joueur rouge est le joueur 2\n");
                printf("Le joueur vert est le joueur 3\n");
                printf("Le joueur jaune est le joueur 4\n");
                return 0;
            }
        }while(R1 == R2);
    }
    if(i == j && i < k && i < l)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur rouge est le joueur 1\n");
                printf("Le joueur vert est le joueur 2\n");
                printf("Le joueur jaune est le joueur 3\n");
                printf("Le joueur bleu est le joueur 4\n");
                return 1;
            }
            else
            {
                printf("\nLe joueur bleu est le joueur 1\n");
                printf("Le joueur rouge est le joueur 2\n");
                printf("Le joueur vert est le joueur 3\n");
                printf("Le joueur jaune est le joueur 4\n");
                return 0;
            }
        }while(R1 == R2);
    }
    if(i == k && i < j && i < l)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur bleu, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur vert,  qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur vert est le joueur 1\n");
                printf("Le joueur jaune est le joueur 2\n");
                printf("Le joueur bleu est le joueur 4\n");
                printf("Le joueur rouge est le joueur 4\n");
                return 2;
            }
            else
            {
                printf("\nLe joueur bleu est le joueur 1\n");
                printf("Le joueur rouge est le joueur 2\n");
                printf("Le joueur vert est le joueur 4\n");
                printf("Le joueur jaune est le joueur 4\n");
                return 0;
            }
        }while(R1 == R2);
    }
    if(j == l && j < i && j < k)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur rouge, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur jaune, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur jaune est le joueur 1\n");
                printf("Le joueur bleu est le joueur 2\n");
                printf("Le joueur rouge est le joueur 3\n");
                printf("Le joueur vert est le joueur 4\n");
                return 3;
            }
            else
            {
                printf("\nLe joueur rouge est le joueur 1\n");
                printf("Le joueur vert est le joueur 2\n");
                printf("Le joueur jaune est le joueur 3\n");
                printf("Le joueur bleu est le joueur 4\n");
                return 1;
            }
        }while(R1 == R2);
    }
    if (k == l && k < i && k < j)
    {
        int D1; int D2; int D3; int D4;
        int R1; int R2;
        do
        {
            printf("\nLes joueurs relancent chacun deux dés pour les departager \n");
            D1 = LancerD();
            printf("%d\t", D1);
            D2 = LancerD();
            printf("%d\n\n", D2);
            D3 = LancerD();
            printf("%d\t", D3);
            D4 = LancerD();
            printf("%d\n\n", D4);
            R1 = D1 + D2;
            R2 = D3 + D4;
            printf("\nLe premier joueur, le joueur vert, qui a relancé les dés a obtenu : %d\n", R1);
            printf("Le deuxieme joueur, le joueur jaune, qui a relancé les dés a obtenu : %d\n", R2);
            if (R1 > R2)
            {
                printf("\nLe joueur jaune est le joueur 1\n");
                printf("Le joueur bleu est le joueur 2\n");
                printf("Le joueur rouge est le joueur 3\n");
                printf("Le joueur vert est le joueur 4\n");
                return 3;
            }
            else
            {
                printf("\nLe joueur vert est le joueur 1\n");
                printf("Le joueur jaune est le joueur 2\n");
                printf("Le joueur bleu est le joueur 3\n");
                printf("Le joueur rouge est le joueur 4\n");
                return 2;
            }
        }while(R1 == R2);
    }
}
