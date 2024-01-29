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


//Sous programme de la capacit� sp�ciale du vaisseau de valeur 1 : Station de Combat. Ce dernier peut se d�placer et attaquer une deuxi�me pendant le tour de jeu
void Station_de_Combat(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{

    int i; int j; int l = 0;
    printf("Entrez la ligne de votre vaisseau\n");
    scanf("%d", &i);
    printf("Entrez la colonne de votre vaisseau\n");
    scanf("%d", &j);
    printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
	scanf("%d", &l);
    if (tab_Plateau[i - 1][j - 1].Valeur == 1)
    {
        if (tab_Plateau[i - 1][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7 && tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
            {
                Fight_1(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
            }
            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7 && tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
            {
                Fight_2(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
            }
            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7 && tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
            {
                Fight_3(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
            }
            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7 && tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
            {
                Fight_4(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
            }
            else
                printf("Il n'y a pas de vaisseaux autour � attaquer\n");
        }
        else
            printf("Cette case ne contient pas un de vos vaisseaux, r�essayez avec une autre coordonn�e\n");
    }
    else
        printf("Le vaisseau initial n'est pas une station de combat et vous ne pouvez pas utiliser cette capacit� sp�ciale\n");
}


//Sous programme de la capacit� sp�ciale du vaisseau de valeur 2 : Vaisseau amiral. Ce dernier peut transporter un vaisseau si celui-ci est plac� sur une des positions autour de celles du vaisseau amiral
void Vaisseau_Amiral(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k = 0; int l = 0; int m = 0; int z = 0; int Choix = 0; int choix = 0;
    printf("Entrez la ligne du vaisseau initial\n");
    scanf("%d", &i);
    printf("Entrez la colonne du vaisseau initial\n");
    scanf("%d", &j);
    printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
	scanf("%d", &l);
	while (l != 1 && l !=2 && l != 3)
    {
        printf("Vous n'avez pas de vaisseau portant ce num�ro, r�essayez\n");
        scanf("%d", &l);
    }
    printf("Entrez le num�ro du vaisseau que vous voulez transporter (num�ro d'initialisation)\n");
    scanf("%d", &m);
    while (m != 1 && m != 2 && m != 3)
    {
        printf("Vous n'avez pas de vaisseau portant ce num�ro, r�essayez\n");
        scanf("%d", &m);
    }
    if (tab_Plateau[i - 1][j - 1].Valeur == 2)
    {
        if (tab_Plateau[i - 1][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            printf("Dans quelle direction se trouve le vaisseau que vous voulez transporter ? (1.Haut gauche 2.Haut  3.Haut droite  4.Droite  5.Bas droite  6.Bas  7.Bas gauche  8.Gauche)\n");
            scanf("%d", &Choix);
            while (Choix != 1 && Choix != 2 && Choix != 3 && Choix != 4 && Choix != 5 && Choix != 6 && Choix != 7 && Choix != 8)
            {
                printf(" Choix invalide, r�essayez\n");
                scanf("%d", &Choix);
            }
            if (Choix == 1 && tab_Plateau[i - 2][j - 2].Valeur > 0 && tab_Plateau[i - 2][j - 2].Valeur < 7)
            {
                if (tab_Plateau[i - 2][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i - 2][j - 2].Valeur;
                    tab_Plateau[i - 2][j - 2].Valeur = 0;
                    tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche  5.Arr�t du d�placement)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 5)
                            k++;
                            if (k == 1)
                                Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 2 && tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
            {
                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i - 2][j - 1].Valeur;
                    tab_Plateau[i - 2][j - 1].Valeur = 0;
                    tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 3 && tab_Plateau[i - 2][j].Valeur > 0 && tab_Plateau[i - 2][j].Valeur < 7)
            {
                if (tab_Plateau[i - 2][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i - 2][j].Valeur;
                    tab_Plateau[i - 2][j].Valeur = 0;
                    tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 4 && tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
            {
                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i - 1][j].Valeur;
                    tab_Plateau[i - 1][j].Valeur = 0;
                    tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 5 && tab_Plateau[i][j].Valeur > 0 && tab_Plateau[i][j].Valeur < 7)
            {
                if (tab_Plateau[i][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i][j].Valeur;
                    tab_Plateau[i][j].Valeur = 0;
                    tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 6 && tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
            {
                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i][j - 1].Valeur;
                    tab_Plateau[i][j - 1].Valeur = 0;
                    tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 7 && tab_Plateau[i][j - 2].Valeur > 0 && tab_Plateau[i][j - 2].Valeur < 7)
            {
            if (tab_Plateau[i][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i][j - 2].Valeur;
                    tab_Plateau[i][j - 2].Valeur = 0;
                    tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
            if (Choix == 8 && tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
            {
                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                {
                    z = tab_Plateau[i - 1][j - 2].Valeur;
                    tab_Plateau[i - 1][j - 2].Valeur = 0;
                    tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 0;
                    while (k < 2)
                    {
                        color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
                        printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche)\n");
                        scanf("%d", &choix);
                        while (choix != 1 && choix != 2 && choix != 3 && choix != 4)
                        {
                            printf("Choix invalide, r�essayez\n");
                            scanf("%d", &choix);
                        }
                        if (choix == 1)
                        {
                            if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 2][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i = i - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 2)
                        {
                            if (tab_Plateau[i - 1][j].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 3)
                        {
                            if (tab_Plateau[i][j - 1].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                            {
                                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i][j - 1].Valeur == 0)
                            {
                                tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                i++;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                        if (choix == 4)
                        {
                            if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                                printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                            if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                            {
                                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                                if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                                    printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
                            }
                            if (tab_Plateau[i - 1][j - 2].Valeur == 0)
                            {
                                tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                                tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                                tab_Plateau[i - 1][j - 1].Valeur = 0;
                                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                                tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                                j = j - 1;
                                if (k == 1)
                                    Voyage(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, z, m);
                            }
                        }
                    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
                    k++;
                    }
                }
                else
                {
                    printf("Ce vaisseau ne vous appartient pas\n");
                }
            }
        }
        else
            printf("Cette case ne contient pas un de vos vaisseaux, r�essayez avec une autre coordonn�e\n");
    }
    else
        printf("Le vaisseau initial n'est pas un vaisseau amiral et vous ne pouvez pas utiliser sa capacit� sp�ciale\n");
}


//Sous programme du d�placement du vaisseau amiral (2), avant de d�poser le vaisseau transport�
void Voyage(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int z, int m)
{
    int CHOIX = 0;
    printf("O� voulez vous d�poser le vaisseau transport� ? (1.Haut gauche 2.Haut  3.Haut droite  4.Droite  5.Bas droite  6.Bas  7.Bas gauche  8.Gauche)\n");
    scanf("%d", &CHOIX);
    while (CHOIX != 1 && CHOIX != 2 && CHOIX != 3 && CHOIX != 4 && CHOIX != 5 && CHOIX != 6 && CHOIX != 7 && CHOIX != 8)
    {
        printf(" Choix invalide, r�essayez\n");
        scanf("%d", &CHOIX);
    }
    if (CHOIX == 1)
    {
        if (tab_Plateau[i - 2][j - 2].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i - 2][j - 2].Valeur > 0 && tab_Plateau[i - 2][j - 2].Valeur < 7)
        {
            if (tab_Plateau[i - 2][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i - 2][j - 2].Valeur == 0)
        {
            tab_Plateau[i - 2][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i - 2][j - 2].Valeur = z;
            if (m == 1)
                tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m== 3)
                tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
    if (CHOIX == 2)
    {
        if (tab_Plateau[i - 2][j - 1].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
        {
            if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i - 2][j - 1].Valeur == 0)
        {
            tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i - 2][j - 1].Valeur = z;
            if (m == 1)
                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
    if (CHOIX == 3)
    {
        if (tab_Plateau[i - 2][j].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i - 2][j].Valeur > 0 && tab_Plateau[i - 2][j].Valeur < 7)
        {
            if (tab_Plateau[i - 2][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i - 2][j].Valeur == 0)
        {
            tab_Plateau[i - 2][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i - 2][j].Valeur = z;
            if (m == 1)
                tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m== 3)
                tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
    if (CHOIX == 4)
    {
        if (tab_Plateau[i - 1][j].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
        {
            if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i - 1][j].Valeur == 0)
        {
            tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i - 1][j].Valeur = z;
            if (m == 1)
                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m- 1] = 3;
        }
    }
    if (CHOIX == 5)
    {
        if (tab_Plateau[i][j].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i][j].Valeur > 0 && tab_Plateau[i][j].Valeur < 7)
        {
            if (tab_Plateau[i][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i][j].Valeur == 0)
        {
            tab_Plateau[i][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i][j].Valeur = z;
            if (m == 1)
                tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][m- 1] = 3;
        }
    }
    if (CHOIX == 6)
    {
        if (tab_Plateau[i][j - 1].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
        {
            if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i][j - 1].Valeur == 0)
        {
            tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i][j - 1].Valeur = z;
            if (m == 1)
                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
    if (CHOIX == 7)
    {
        if (tab_Plateau[i][j - 2].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i][j - 2].Valeur > 0 && tab_Plateau[i][j - 2].Valeur < 7)
        {
            if (tab_Plateau[i][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i][j - 2].Valeur == 0)
        {
            tab_Plateau[i][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i][j - 2].Valeur = z;
            if (m == 1)
                tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m- 1] = 1;
            if (m == 2)
                tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
    if (CHOIX == 8)
    {
        if (tab_Plateau[i - 1][j - 2].Valeur > 6)
            printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
        if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
        {
            if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
            if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                printf("Cette emplacement n'est pas disponible, il y a un vaisseau ennemi dessus\n");
        }
        if (tab_Plateau[i - 1][j - 2].Valeur == 0)
        {
            tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
            tab_Plateau[i - 1][j - 2].Valeur = z;
            if (m == 1)
                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 1;
            if (m == 2)
                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 2;
            if (m == 3)
                tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][m - 1] = 3;
        }
    }
}


//Sous programme de la capacit� sp�ciale du vaisseau de valeur 3 : Destroyer. Ce dernier peut intervertir sa position avec un autre vaisseau
void Destroyer(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i = 0; int j = 0; int k = 0; int l = 0;
    printf("Entrez la ligne du vaisseau initial\n");
    scanf("%d", &i);
    printf("Entrez la colonne du vaisseau initial\n");
    scanf("%d", &j);
    printf("Entrez la ligne du vaisseau cible\n");
    scanf("%d", &k);
    printf("Entrez la colonne du vaisseau cible\n");
    scanf("%d", &l);
    if (((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 1) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 2) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 3)) && ((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 1) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 2) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 3)) && ((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 1) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 2) && (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 3)))
        printf("Ce vaisseau initial ne vous appartient pas\n");
    if (((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 1) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 2) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] != 3)) && ((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 1) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 2) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] != 3)) && ((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 1) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 2) && (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] != 3)))
        printf("Ce vaisseau cible ne vous appartient pas\n");
    if ((((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 1) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 2) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 3)) || ((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 1) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 2) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 3)) || ((tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 1) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 2) || (tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 3))) && (((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 1) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 2) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][0] == 3)) || ((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 1) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 2) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][1] == 3)) || ((tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 1) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 2) || (tab_Plateau[k - 1][l - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][2] == 3))))
        {
            if (tab_Plateau[i - 1][j - 1].Valeur == 3)
            {
                tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[k - 1][l - 1].Valeur;
                tab_Plateau[k - 1][l - 1].Valeur = 3;
            }
            else
            {
                printf("Le vaisseau initial n'est pas un destroyer et vous ne pouvez pas utiliser sa capacit� sp�ciale\n");
            }
        }
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}


//Sous programme de la capacit� sp�ciale de vaisseau de valeur 4 : Fr�gate. Cette derni�re peut se reconfigurer en Destroyer ou Intercepteur
void Fregate(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k; int Choix = 0;
    printf("Entrez la ligne du vaisseau dont vous voulez modifier la valeur\n");
    scanf("%d", &i);
    printf("Entrez la colonne du vaisseau dont vous voulez modifier la valeur\n");
    scanf("%d", &j);
    printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
    scanf("%d", &k);
    if (tab_Plateau[i - 1][j - 1].Valeur == 4)
    {
        if (tab_Plateau[i - 1][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            printf("Que voulez vous faire ? (1.Augmenter sa valeur (+1)  2.Diminuer sa valeur (-1))\n");
            scanf("%d", &Choix);
            while(Choix != 1 && Choix != 2)
            {
                printf("Choix invalide, r�essayez\n");
                scanf("%d", &Choix);
            }
            if (Choix == 1)
            {
                tab_Plateau[i - 1][j - 1].Valeur = 5;
                tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 1][j - 1].Valeur;
            }
            if (Choix == 2)
            {
                tab_Plateau[i - 1][j - 1].Valeur = 3;
                tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 1][j - 1].Valeur;
            }
        }
        else
            printf("Cette case ne contient pas un de vos vaisseaux, r�essayez avec une autre coordonn�e\n");
    }
    else
        printf("Le vaisseau initial n'est pas une fr�gate et vous ne pouvez pas utiliser sa capacit� sp�ciale\n");
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}


//Sous programme de la capacit� sp�ciale du vaisseau de valeur 6 : Eclairer. Ce dernier peut se reconfigurer en un vaisseau de valeur diff�rente
void Eclaireur(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k;
    printf("Entrez la ligne du vaisseau que vous voulez reconfigurer\n");
    scanf("%d", &i);
    printf("Entrez la colonne du vaisseau que vous voulez reconfigurer\n");
    scanf("%d", &j);
    printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
    scanf("%d", &k);
    if (tab_Plateau[i - 1][j - 1].Valeur == 6)
    {
        if (tab_Plateau[i - 1][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            do
            {
                tab_Plateau[i - 1][j - 1].Valeur = LancerD();
            }while(tab_Plateau[i - 1][j - 1].Valeur == tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1]);
            tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 1][j - 1].Valeur;
        }
        else
        {
            printf("Cette case ne contient pas un de vos vaisseau, r�essayez avec une autre coordonn�e\n");
        }
    }
    else
    {
        printf("Le vaisseau n'est pas un �claireur et vous ne pouvez pas utiliser sa capacit� sp�ciale\n");
    }
    printf("La nouvelle valeur de votre vaisseau est %d\n", tab_Plateau[i - 1][j - 1].Valeur);
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}
