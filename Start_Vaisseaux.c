#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Types_structures.h"
#include "Initialisation.h"
#include "Affichage.h"
#include "Outils.h"
#include "Start_Vaisseaux.h"


//Sous programme permettant d'initialiser les vaisseaux d'un joueur
void Initialisation_Vaisseaux(S_Joueur tab_Joueurs[],  int NbJ)
{
    int Choix = 0;
    for (int i = 0; i < NbJ; i++)
    {
        if (tab_Joueurs[i].Couleur == 11)
            printf("\nOn initialise les vaisseaux du Joueur bleu\n");
        if (tab_Joueurs[i].Couleur == 12)
            printf("\nOn initialise les vaisseaux du Joueur rouge\n");
        if (tab_Joueurs[i].Couleur == 10)
            printf("\nOn initialise les vaisseaux du Joueur vert\n");
        if (tab_Joueurs[i].Couleur == 14)
            printf("\nOn initialise les vaisseaux du Joueur jaune\n");
        Creation_Vaisseaux(tab_Joueurs, i);
        printf("Etes vous satisfait de votre lancer ? (1.Oui  2.Non)\n\n");
        do
        {
            scanf("%d", &Choix);
            if (Choix != 1 && Choix != 2) printf("No. Invalide\n");
        }while(Choix !=1 && Choix != 2);
        if (Choix == 2) Creation_Vaisseaux(tab_Joueurs, i);
    }
}


//Sous programme permettant d'initialiser les vaisseaux de tous les joueurs
void Creation_Vaisseaux(S_Joueur tab_Joueurs[], int i)
{
     for (int j = 0; j < 3; j++)
     {
             tab_Joueurs[i].tab_Vaisseaux[j] = LancerD();
             printf("Ton vaisseau no. %d a pour valeur %d \n", j+1, tab_Joueurs[i].tab_Vaisseaux[j]);
     }
}

