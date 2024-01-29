#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Outils.h"
#include "Types_structures.h"
#include "Initialisation.h"
#include "Affichage.h"
#include "Start_Vaisseaux.h"
#include "Premier_Joueur.h"
#include "Deploiement_Vaisseaux.h"


//Sous programmes utilisés tout au long du jeu

//Sous programme permettant de récupérer le résultat d'un lancer de dé aléatoire
int LancerD()
{
   static int first = 0;
   if (first == 0)
   {
      srand (time (NULL));
      first = 1;
   }
   return (rand() %(6) + 1);
}


//Sous programme permettant d'inclure la couleur au programme et de pouvoir afficher le texte dans la couleur souhaitée
void color (int couleurDuTexte, int couleurDuFond)
{
     HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
}


//Sous programme permettant de poser un cube Quantum sur le plateau de jeu et qui réinitialise la valeur du dé Domination à 1
void Domination(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j;
    if (tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination == 6)
    {
        printf("Entrez la ligne de la planète où vous voulez placer un cube Quantum\n");
        scanf("%d", &i);
        printf("Entrez la colonne de la planète où vous voulez placer un cube Quantum\n");
        scanf("%d", &j);
        if (tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] == 0)
        {
            if (tab_Plateau[i - 1][j - 1].Valeur == 7)
            {
                if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 1)
                {
                    printf("Vous placez un cube Quantum supplémentaire sur cette planète\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
            }
            if (tab_Plateau[i - 1][j - 1].Valeur == 8)
            {
                if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 2)
                {
                    printf("Vous placez un cube Quantum supplémentaire sur cette planète\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
            }
            if (tab_Plateau[i - 1][j - 1].Valeur == 9)
            {
                if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 3)
                {
                    printf("Vous placez un cube Quantum supplémentaire sur cette planète\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
            }
            if (tab_Plateau[i - 1][j - 1].Valeur == 10)
            {
                if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 4)
                {
                    printf("Vous placez un cube Quantum supplémentaire sur cette planète\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
            }
        }
        else
            printf("Vous possédez déjà un cube Quantum sur cette planète, vous ne pouvez pas poser un cube Quantum ici\n");
    tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination = 1;
    }
}
