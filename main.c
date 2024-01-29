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
#include "Actions_de_jeu.h"
#include "Capacites_speciales.h"


//----------------------------------------------------
//Prototypes
void Tour_de_Jeu(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);

void Action(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int *Nb_Actions, int *Nb_Capacites);
void Capacite_speciale(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int *Nb_Actions, int *Nb_Capacites);

//----------------------------------------------------
int main()
{
    SetConsoleOutputCP(1252);
    int NbJ = 0;
    int J1 = 0;
    int Passage = 0;
    printf("Bienvenue au jeu Quantum\n\n");
    printf("Combien de joueurs veulent jouer à Quantum ?\n");
    scanf("%d", &NbJ);

//Initialisation des données et du plateau de jeu
    S_Case tab_Plateau[9][9];
    S_Joueur *tab_Joueurs = NULL;
    tab_Joueurs = malloc(sizeof(S_Joueur) * NbJ);
    if(tab_Joueurs == NULL)
    exit(1);

    Initialisation_Joueurs (tab_Joueurs, NbJ);
    Affichage_Joueurs (tab_Joueurs, NbJ);

    Initialisation_Plateau (tab_Plateau, NbJ);
    Affichage_Plateau (tab_Plateau, tab_Joueurs, NbJ, J1);

    Initialisation_Vaisseaux (tab_Joueurs, NbJ);
    J1 = Determination_1er_Joueur (tab_Joueurs, NbJ);
    Deploiement_Vaisseaux (tab_Joueurs, tab_Plateau, NbJ, J1);

//Corps de jeu
    do
    {
        Tour_de_Jeu (tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        Passage++;
    }while(tab_Joueurs[0].Nb_cubes_Quantum != 0 || tab_Joueurs[1].Nb_cubes_Quantum != 0 || tab_Joueurs[2].Nb_cubes_Quantum != 0 || tab_Joueurs[3].Nb_cubes_Quantum != 0);

//Conditions de victoire
    if (tab_Joueurs[0].Nb_cubes_Quantum == 0)
        printf("Le joueur bleu remporte la partie\n");
    if (tab_Joueurs[1].Nb_cubes_Quantum == 0)
        printf("Le joueur rouge remporte la partie\n");
    if (tab_Joueurs[2].Nb_cubes_Quantum == 0)
        printf("Le joueur vert remporte la partie\n");
    if (tab_Joueurs[3].Nb_cubes_Quantum == 0)
        printf("Le joueur jaune remporte la partie\n");
    free(tab_Joueurs);
    return 0;
}

//----------------------------------------------------
//Sous-programmes

//Sous programme permettant au joueur de choisir ce qu'il veut faire en premier lorsqu'il commence son tour de jeu
void Tour_de_Jeu(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int Choix = 0;
    int Nb_Actions = 0;
    int Nb_Capacites = 0;
    while(Nb_Actions < 3 || Nb_Capacites < 3)
    {
        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
        printf("\nQue voulez vous faire ?\n");
        printf("\n1. Faire une action de jeu");
        printf("\n2. Utiliser une capacité spéciale de vaisseaux");
        printf("\n3. Ne rien faire, fin de mon tour de jeu\n");
        scanf("%d", &Choix);
        while(Choix != 1 && Choix != 2 && Choix != 3)
        {
            printf("Choix non valide, réessayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
            Action(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, &Nb_Actions, &Nb_Capacites);
        if (Choix == 2)
            Capacite_speciale(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, &Nb_Actions, &Nb_Capacites);
        if (Choix == 3)
        {
            Nb_Actions = 3; Nb_Capacites = 3;
        }
    }
            color (15,0);
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}


//Sous programme listant les actions que peut réaliser le joueur (menu déroulant récupérant le choix du joueur)
void Action(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int *Nb_Actions, int *Nb_Capacites)
{
    int j;
    for (j = 0; j < 3; j++)
    {
        printf("Ton vaisseau no. %d a pour valeur %d \n", j+1, tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[j]);
    }
    while(*Nb_Actions < 3)
    {
        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
        int Choix = 0;
        printf("\nQue voulez vous faire ?\n");
        printf("\n1. Reconfigurer un vaisseau (changer sa valeur)");
        printf("\n2. Réparer un vaisseau et le déployer de la casse au plateau");
        printf("\n3. Déplacer et/ou attaquer un vaisseau ennemi");
        printf("\n4. Construire un cube Quantum (compte pour 2 actions)");
        printf("\n5. Recherche (+1 au Cpt_Recherche)");
        printf("\n6. Utiliser une capacité spéciale de vaisseau");
        printf("\n7. Finir son tour de jeu\n");
        scanf("%d", &Choix);
        switch(Choix)
        {
            case 1 : Reconfigurer(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 2 : Reparer(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 3 : Move_Fight(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 4 : Cube_Quantum(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 5 : Recherche(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 6 : Capacite_speciale(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, *&Nb_Actions, *&Nb_Capacites);
                break;
            case 7 : *Nb_Actions = 3;
                break;
            default : printf("Action inexistante, réessayez\n");
        }
        if (Choix == 1 || Choix == 2 || Choix == 3 || Choix == 5)
            *Nb_Actions = *Nb_Actions + 1;
        if (Choix == 4)
            *Nb_Actions = *Nb_Actions + 2;
    }
    color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
    if (*Nb_Actions > 2)
        printf("Plus d'action disponible pour ce tour\n");
}


//Sous programme listant les capacités spéciales de vaisseaux que peut réaliser le joueur (menu déroulant récupérant le choix du joueur)
void Capacite_speciale(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int *Nb_Actions, int *Nb_Capacites)
{
    int j;
    for (j = 0; j < 3; j++)
    {
        printf("Ton vaisseau no. %d a pour valeur %d \n", j+1, tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[j]);
    }
    while(*Nb_Capacites < 3)
    {
        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
        int Choix = 0;
        printf("\nQue voulez vous faire ?\n");
        printf("\n1. Utiliser ATTAQUE");
        printf("\n2. Utiliser TRANSPORT");
        printf("\n3. Utiliser WARP");
        printf("\n4. Utiliser MODIFIER");
        printf("\n5. Utiliser RECONFIGURATION GRATUITE");
        printf("\n6. Faire une action de jeu");
        printf("\n7. Finir son tour de jeu\n");
        scanf("%d", &Choix);
        switch(Choix)
        {
            case 1 : Station_de_Combat(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 2 : Vaisseau_Amiral(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 3 : Destroyer(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 4 : Fregate(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 5 : Eclaireur(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
                break;
            case 6 : Action(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, *&Nb_Actions, *&Nb_Capacites);
                break;
            case 7 : *Nb_Capacites = 3;
                break;
            default : printf("\nCapacité inexistante, réessayez\n");
        }
        *Nb_Capacites = *Nb_Capacites + 1;
    }
}











