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


//Sous programme de l'action *Reconfigurer. Effectue un nouveau lancer de d� pour attribuer une nouvelle valeur au d� cibl� par le joueur
void Reconfigurer(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k;
    printf("Entrez la ligne du vaisseau que vous voulez reconfigurer\n");
    scanf("%d", &i);
    printf("Entrez la colonne du vaisseau que vous voulez reconfigurer\n");
    scanf("%d", &j);
    printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
    scanf("%d", &k);
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
    printf("La nouvelle valeur de votre vaisseau est %d\n", tab_Plateau[i - 1][j - 1].Valeur);
    Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}


//Sous programme de l'action *D�ployer. Dans le cas o� un vaisseau est d�truit au combat, permet au joueur de repositionner son vaisseau sur une position orbitale d'une plan�te o� il poss�de un cube Quantum
void Reparer(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k; int Choix = 0;
	if (tab_Joueurs[(J1 + Passage)%NbJ].Nb_Vaisseaux_Casse > 0)
    {
		printf("Entrez la ligne de la planete o� vous voulez redeployer votre vaisseau\n");
		scanf("%d", &i);
		printf("Entrez la colonne de la planete o� vous voulez redeployer votre vaisseau\n");
		scanf("%d", &j);
		printf("Quel est le num�ro de votre vaisseau � la casse (num�ro d'initialisation) ?\n");
		scanf("%d", &k);
		while (k != 1 && k != 2 && k!= 3)
        {
			printf("Num�ro invalide, r�essayez\n");
			scanf("%d", &k);
        }
		if (tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] == 1)
        {
			if (tab_Plateau[i - 2][j - 1].Valeur == 0 || tab_Plateau[i][j - 1].Valeur == 0 || tab_Plateau[i - 1][j - 2].Valeur == 0 || tab_Plateau[i - 1][j].Valeur == 0)
            {
				printf("Sur quelle position orbitale voulez vous red�ployer votre vaisseau ? (1. Haut  2. Bas  3. Gauche  4.Droite)\n");
				scanf("%d", &Choix);
				while (Choix != 1 && Choix != 2 && Choix != 3 && Choix != 4)
                {
					printf("Choix invalide, r�essayez\n");
					scanf("%d", &Choix);
                }
                if (Choix == 1 && tab_Plateau[i - 2][j - 1].Valeur != 0)
					printf("Il y a d�j� un vaisseau sur cette position orbitale, r�essayez avec un autre emplacement ou faites une autre action\n");
				if (Choix == 1 && tab_Plateau[i - 2][j - 1].Valeur == 0)
                {
					printf("Votre vaisseau se red�ploye sur la position orbitale Haut\n");
					tab_Plateau[i - 2][j - 1].Valeur = LancerD();
					tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 2][j - 1].Valeur;
					if (k == 1)
                        tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 1;
                    if (k == 2)
                        tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 2;
                    if (k == 3)
                        tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 3;
                }
                if (Choix == 2 && tab_Plateau[i][j - 1].Valeur != 0)
					printf("Il y a d�j� un vaisseau sur cette position orbitale, r�essayez avec un autre emplacement ou faites une autre action\n");
				if (Choix == 2 && tab_Plateau[i][j - 1].Valeur == 0)
                {
					printf("Votre vaisseau se red�ploye sur la position orbitale Bas\n");
					tab_Plateau[i][j - 1].Valeur = LancerD();
					tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i][j - 1].Valeur;
					if (k == 1)
                        tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 1;
                    if (k == 2)
                        tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 2;
                    if (k == 3)
                        tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 3;
                }
                if (Choix == 3 && tab_Plateau[i - 1][j - 2].Valeur != 0)
					printf("Il y a d�j� un vaisseau sur cette position orbitale, r�essayez avec un autre emplacement ou faites une autre action\n");
				if (Choix == 3 && tab_Plateau[i - 1][j - 2].Valeur == 0)
                {
					printf("Votre vaisseau se red�ploye sur la position orbitale Gauche\n");
					tab_Plateau[i - 1][j - 2].Valeur = LancerD();
					tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 1][j - 2].Valeur;
					if (k == 1)
                        tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 1;
                    if (k == 2)
                        tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 2;
                    if (k == 3)
                        tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 3;
                }
                if (Choix == 4 && tab_Plateau[i - 1][j].Valeur != 0)
					printf("Il y a d�j� un vaisseau sur cette position orbitale, r�essayez avec un autre emplacement ou faites une autre action\n");
				if (Choix == 4 && tab_Plateau[i - 1][j].Valeur == 0)
                {
					printf("Votre vaisseau se red�ploye sut la position orbitale Droite\n");
					tab_Plateau[i - 1][j].Valeur = LancerD();
					tab_Joueurs[(J1 + Passage)%NbJ].tab_Vaisseaux[k - 1] = tab_Plateau[i - 1][j].Valeur;
					if (k == 1)
                        tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 1;
                    if (k == 2)
                        tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 2;
                    if (k == 3)
                        tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][k - 1] = 3;
                }
				            }
			else
				printf("Toutes les positions orbitales de cette plan�te sont occup�es, vous ne pouvez pas effectuer cette action\n");
        }
		else
			printf("Vous n'avez pas de cube Quantum sur cette plan�te, vous ne pouvez pas effectuer cette action\n");
    }
	else
    {
	printf("Vous n'avez pas de vaisseaux dans votre casse, vous ne pouvez pas effectuer cette action\n");
    }
	Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
}

//Sous programme de l'action *Se d�placer/Attaquer. Il permet le d�placement des vaisseaux sur le plateau de jeu
void Move_Fight(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k = 0; int l = 0; int Choix = 0;
	printf("Entrez la ligne du  vaisseau que vous voulez deplacer\n");
	scanf("%d", &i);
	printf("Entrez la colonne du vaisseau que vous voulez deplacer\n");
	scanf("%d", &j);
	printf("Entrez le num�ro de votre vaisseau (num�ro d'initialisation)\n");
	scanf("%d", &l);
	while (l != 1 && l !=2 && l != 3)
    {
        printf("Vous n'avez pas de vaisseau portant ce num�ro, r�essayez\n");
        scanf("%d", &l);
    }
	if (tab_Plateau[i - 1][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
    {
		while (k < tab_Plateau[i - 1][j - 1].Valeur)
        {
            color(tab_Joueurs[(J1 + Passage)%NbJ].Couleur, 0);
            printf("Dans quelle direction voulez vous aller ? (1. Haut  2.Droite  3.Bas  4.Gauche 0. Arr�ter le d�placement)\n");
            if (tab_Plateau[i - 1][j - 1].Valeur == 5)
                printf("(5. Haut Gauche  6. Haut droite  7. Bas droite  8. Bas gauche)\n");
            scanf("%d", &Choix);
            while (Choix != 1 && Choix != 2 && Choix != 3 && Choix != 4 && Choix != 5 && Choix != 6 && Choix != 7 && Choix != 8 && Choix != 0)
            {
				printf("Choix invalide, r�essayez\n");
				scanf("%d", &Choix);
            }
            if (tab_Plateau[i - 1][j - 1].Valeur == 5)
            {
                if (Choix == 5)
                {
                    if (tab_Plateau[i - 2][j - 2].Valeur > 6)
                        printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                    if (tab_Plateau[i - 2][j - 2].Valeur > 0 && tab_Plateau[i - 2][j - 2].Valeur < 7)
                    {
                        if (tab_Plateau[i - 2][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                            printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                        if (tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        {
                            Fight_5(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                            k = 12;
                        }
                    }
                    if (tab_Plateau[i - 2][j - 2].Valeur == 0 && k < 7)
                    {
                        tab_Plateau[i - 2][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                        tab_Plateau[i - 2][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                        tab_Plateau[i - 1][j - 1].Valeur = 0;
                        tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                        tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                        i = i - 1; j = j - 1;

                    }
                }
                if (Choix == 6)
                {
                    if (tab_Plateau[i - 2][j].Valeur > 6)
                        printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                    if (tab_Plateau[i - 2][j].Valeur > 0 && tab_Plateau[i - 2][j].Valeur < 7)
                    {
                        if (tab_Plateau[i - 2][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                            printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                        if (tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        {
                            Fight_6(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                            k = 12;
                        }
                    }
                    if (tab_Plateau[i - 2][j].Valeur == 0 && k < 7)
                    {
                        tab_Plateau[i - 2][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                        tab_Plateau[i - 2][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                        tab_Plateau[i - 1][j - 1].Valeur = 0;
                        tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                        tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                        i = i - 1; j = j + 1;
                    }
                }
                if (Choix == 7)
                {
                    if (tab_Plateau[i][j].Valeur > 6)
                        printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                    if (tab_Plateau[i][j].Valeur > 0 && tab_Plateau[i][j].Valeur < 7)
                    {
                        if (tab_Plateau[i][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                            printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                        if (tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        {
                            Fight_7(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                            k = 12;
                        }
                    }
                    if (tab_Plateau[i][j].Valeur == 0 && k < 7)
                    {
                        tab_Plateau[i][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                        tab_Plateau[i][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                        tab_Plateau[i - 1][j - 1].Valeur = 0;
                        tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                        tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                        i = i + 1; j = j + 1;
                    }
                }
                if (Choix == 8)
                {
                    if (tab_Plateau[i][j - 2].Valeur > 6)
                        printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                    if (tab_Plateau[i][j - 2].Valeur > 0 && tab_Plateau[i][j - 2].Valeur < 7)
                    {
                        if (tab_Plateau[i][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                            printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                        if (tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        {
                            Fight_8(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                            k = 12;
                        }
                    }
                    if (tab_Plateau[i][j - 2].Valeur == 0 && k < 7)
                    {
                        tab_Plateau[i][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                        tab_Plateau[i][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                        tab_Plateau[i - 1][j - 1].Valeur = 0;
                        tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                        tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                        i = i + 1; j = j - 1;
                    }
                }
            }
            if (Choix == 0)
            {
                printf("Fin du deplacement\n");
                k = 12;
            }
            if (Choix == 1)
            {
                if (tab_Plateau[i - 2][j - 1].Valeur > 6)
                    printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                if (tab_Plateau[i - 2][j - 1].Valeur > 0 && tab_Plateau[i - 2][j - 1].Valeur < 7)
                {
                    if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                    if (tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    {
                        Fight_1(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                        k = 12;
                    }
                }
                if (tab_Plateau[i - 2][j - 1].Valeur == 0 && k < 7)
                {
                    tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                    tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                    tab_Plateau[i - 1][j - 1].Valeur = 0;
                    tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                    tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                    i = i - 1;
                }
            }
			if (Choix == 2)
            {
                if (tab_Plateau[i - 1][j].Valeur > 6)
                    printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                if (tab_Plateau[i - 1][j].Valeur > 0 && tab_Plateau[i - 1][j].Valeur < 7)
                {
                    if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                    if (tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    {
                        Fight_2(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                        k = 12;
                    }
                }
                if (tab_Plateau[i - 1][j].Valeur == 0 && k < 7)
                {
                    tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                    tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                    tab_Plateau[i - 1][j - 1].Valeur = 0;
                    tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                    tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                    j = j + 1;
                }
            }
			if (Choix == 3)
            {
                if (tab_Plateau[i][j - 1].Valeur > 6)
                    printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                if (tab_Plateau[i][j - 1].Valeur > 0 && tab_Plateau[i][j - 1].Valeur < 7)
                {
                    if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                    if (tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    {
                        Fight_3(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                        k = 12;
                    }
                }
                if (tab_Plateau[i][j - 1].Valeur == 0 && k < 7)
                {
                    tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                    tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                    tab_Plateau[i - 1][j - 1].Valeur = 0;
                    tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                    tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                    i = i + 1;
                }
            }
			if (Choix == 4)
			{
                if (tab_Plateau[i - 1][j - 2].Valeur > 6)
                    printf("Cette emplacement n'est pas disponible, il y a une plan�te dessus\n");
                if (tab_Plateau[i - 1][j - 2].Valeur > 0 && tab_Plateau[i - 1][j - 2].Valeur < 7)
                {
                    if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                        printf("Cette emplacement n'est pas disponible, vous avez d�j� un vaisseau dessus\n");
                    if (tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    {
                        Fight_4(tab_Joueurs, tab_Plateau, NbJ, J1, Passage, i, j, l);
                        k = 12;
                    }
                }
                if (tab_Plateau[i - 1][j - 2].Valeur == 0 && k < 7)
                {
                    tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
                    tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
                    tab_Plateau[i - 1][j - 1].Valeur = 0;
                    tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
                    tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
                    j = j - 1;
                }
			}
			Affichage_Plateau(tab_Plateau, tab_Joueurs, NbJ, J1);
			k++;
        }
    }
	else
		printf("Cette case ne contient pas un de vos vaisseaux et vous ne pouvez pas effectuer cette action\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le haut du vaisseau attaquant
void Fight_1(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i - 2][j - 1].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i - 2][j - 1].Couleur == 11 && tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 1].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 1].Couleur == 12 && tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 1].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 1].Couleur == 10 && tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 1].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 1].Couleur == 14 && tab_Plateau[i - 2][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 1].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i - 2][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i - 2][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i - 2][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i - 2][j - 1].Valeur;
            tab_Plateau[i - 2][j - 1].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers la droite du vaisseau attaquant
void Fight_2(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i - 1][j].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i - 1][j].Couleur == 11 && tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j].Couleur == 12 && tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j].Couleur == 10 && tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j].Couleur == 14 && tab_Plateau[i - 1][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i - 1][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i - 1][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i - 1][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i - 1][j].Valeur;
            tab_Plateau[i - 1][j].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le bas du vaisseau attaquant
void Fight_3(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i][j - 1].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i][j - 1].Couleur == 11 && tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 1].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 1].Couleur == 12 && tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 1].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 1].Couleur == 10 && tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 1].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 1].Couleur == 14 && tab_Plateau[i][j - 1].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 1].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i][j - 1].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i][j - 1].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i][j - 1].Valeur;
            tab_Plateau[i][j - 1].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers la gauche du vaisseau attaquant
void Fight_4(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i - 1][j - 2].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i - 1][j - 2].Couleur == 11 && tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j - 2].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j - 2].Couleur == 12 && tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j - 2].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j - 2].Couleur == 10 && tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j - 2].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 1][j - 2].Couleur == 14 && tab_Plateau[i - 1][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 1][j - 2].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i - 1][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i - 1][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i - 1][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i - 1][j - 2].Valeur;
            tab_Plateau[i - 1][j - 2].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le haut/gauche du vaisseau attaquant
void Fight_5(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i - 2][j - 2].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i - 2][j - 2].Couleur == 11 && tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 2].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 2].Couleur == 12 && tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 2].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 2].Couleur == 10 && tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 2].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j - 2].Couleur == 14 && tab_Plateau[i - 2][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j - 2].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i - 2][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i - 2][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i - 2][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i - 2][j - 2].Valeur;
            tab_Plateau[i - 2][j - 2].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le haut/droite du vaisseau attaquant
void Fight_6(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i - 2][j].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i - 2][j].Couleur == 11 && tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j].Couleur == 12 && tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j].Couleur == 10 && tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i - 2][j].Couleur == 14 && tab_Plateau[i - 2][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i - 2][j].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i - 2][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i - 2][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i - 2][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i - 2][j].Valeur;
            tab_Plateau[i - 2][j].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le bas/droite du vaisseau attaquant
void Fight_7(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i][j].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i][j].Couleur == 11 && tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j].Couleur == 12 && tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j].Couleur == 10 && tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j].Couleur == 14 && tab_Plateau[i][j].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i][j].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i][j].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i][j].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i][j].Valeur;
            tab_Plateau[i][j].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme d�taillant les �tapes de combat dans le cas d'un d�placement vers le bas/gauche du vaisseau attaquant
void Fight_8(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int l)
{
    int x = 0; int y = 0; int Choix = 0;
    x = LancerD();
    y = LancerD();
    x = x + tab_Plateau[i - 1][j - 1].Valeur;
    y = y + tab_Plateau[i][j - 2].Valeur;
    printf("L'attaquant a obtenu %d\n", x);
    printf("Le d�fenseur a obtenu %d\n", y);
    if (x <= y)
    {
        printf("L'attaquant gagne\n");
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination++;
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        if (tab_Plateau[i][j - 2].Couleur == 11 && tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[0].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 2].Num_Vaisseaux[0][l - 1] = 0;
            if (tab_Joueurs[0].Cpt_Domination > 1)
                tab_Joueurs[0].Cpt_Domination = tab_Joueurs[0].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 2].Couleur == 12 && tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[1].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 2].Num_Vaisseaux[1][l - 1] = 0;
            if (tab_Joueurs[1].Cpt_Domination > 1)
                tab_Joueurs[1].Cpt_Domination = tab_Joueurs[1].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 2].Couleur == 10 && tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[2].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 2].Num_Vaisseaux[2][l - 1] = 0;
            if (tab_Joueurs[2].Cpt_Domination > 1)
                tab_Joueurs[2].Cpt_Domination = tab_Joueurs[2].Cpt_Domination - 1;
        }
        if (tab_Plateau[i][j - 2].Couleur == 14 && tab_Plateau[i][j - 2].Couleur != tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
        {
            tab_Joueurs[3].Nb_Vaisseaux_Casse++;
            tab_Plateau[i][j - 2].Num_Vaisseaux[3][l - 1] = 0;
            if (tab_Joueurs[3].Cpt_Domination > 1)
                tab_Joueurs[3].Cpt_Domination = tab_Joueurs[3].Cpt_Domination - 1;
        }
        printf("Voulez vous rester sur votre case ou avancer ? (1. Avancer  2. Rester)\n");
        scanf("%d", &Choix);
        while (Choix != 1 && Choix != 2)
        {
            printf("Choix invalide, r�essayez\n");
            scanf("%d", &Choix);
        }
        if (Choix == 1)
        {
            tab_Plateau[i][j - 2].Valeur = tab_Plateau[i - 1][j - 1].Valeur;
            tab_Plateau[i - 1][j - 1].Valeur = 0;
            tab_Plateau[i][j - 2].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1];
            tab_Plateau[i - 1][j - 1].Num_Vaisseaux[(J1 + Passage)%NbJ][l - 1] = 0;
            tab_Plateau[i][j - 2].Couleur = tab_Joueurs[(J1 + Passage)%NbJ].Couleur;
        }
        if (Choix == 2)
        {
            printf("Le vaisseau d�fenseur est detruit et votre vaisseau reste o� il est\n");
            tab_Plateau[i - 1][j - 1].Valeur = tab_Plateau[i][j - 2].Valeur;
            tab_Plateau[i][j - 2].Valeur = 0;
        }
    }
    if (x > y)
        printf("Le d�fenseur gagne\n");
}


//Sous programme de l'action *Construire. Permet au joueur de placer un cube Quantum sur une plan�te s'il l n'en poss�de pas d�j� dessus et si la somme des valeurs de ses vaisseaux plac�s sur les positions orbitales est �gale � la valeur de la plan�te
void Cube_Quantum(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    int i; int j; int k = 0;
    printf("Entrez la ligne de la plan�te o� vous voulez placer un cube Quantum\n");
    scanf("%d", &i);
    printf("Entrez la colonne de la plan�te o� vous voulez placer un cube Quantum\n");
    scanf("%d", &j);
    if (tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] == 0)
    {
        if (tab_Plateau[i - 1][j - 1].Valeur == 7)
        {
            if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 1)
            {
                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 2][j - 1].Valeur;
                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 1].Valeur;
                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 2].Valeur;
                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 1][j].Valeur;
                if (k == tab_Plateau[i - 1][j - 1].Valeur)
                {
                    printf("Vous placez un cube Quantum suppl�mentaire sur cette plan�te\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Impossible de poser un cube Quantum sur cette plan�te\n");
            }
            else
                printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
        }
        if (tab_Plateau[i - 1][j - 1].Valeur == 8)
        {
            if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 2)
            {
                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 2][j - 1].Valeur;
                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 1].Valeur;
                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 2].Valeur;
                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 1][j].Valeur;
                if (k == tab_Plateau[i - 1][j - 1].Valeur)
                {
                    printf("Vous placez un cube Quantum suppl�mentaire sur cette plan�te\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Impossible de poser un cube Quantum sur cette plan�te\n");
            }
            else
                printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
        }
        if (tab_Plateau[i - 1][j - 1].Valeur == 9)
        {
            if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 3)
            {
                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 2][j - 1].Valeur;
                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 1].Valeur;
                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 2].Valeur;
                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 1][j].Valeur;
                if (k == tab_Plateau[i - 1][j - 1].Valeur)
                {
                    printf("Vous placez un cube Quantum suppl�mentaire sur cette plan�te\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Impossible de poser un cube Quantum sur cette plan�te\n");
            }
            else
                printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
        }
        if (tab_Plateau[i - 1][j - 1].Valeur == 10)
        {
            if (tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum < 4)
            {
                if (tab_Plateau[i - 2][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 2][j - 1].Valeur;
                if (tab_Plateau[i][j - 1].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 1].Valeur;
                if (tab_Plateau[i - 1][j - 2].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i][j - 2].Valeur;
                if (tab_Plateau[i - 1][j].Couleur == tab_Joueurs[(J1 + Passage)%NbJ].Couleur)
                    k = k + tab_Plateau[i - 1][j].Valeur;
                if (k == tab_Plateau[i - 1][j - 1].Valeur)
                {
                    printf("Vous placez un cube Quantum suppl�mentaire sur cette plan�te\n");
                    tab_Joueurs[(J1 + Passage)%NbJ].Nb_cubes_Quantum -= 1;
                    tab_Plateau[i - 1][j - 1].Nb_Cubes_Quantum ++;
                    tab_Plateau[i - 1][j - 1].Cubes_Quantum[(J1 + Passage)%NbJ] = 1;
                }
                else
                    printf("Impossible de poser un cube Quantum sur cette plan�te\n");
            }
            else
                printf("Nombre maximum de cubes Quantum atteint, vous ne pouvez pas placer un cube Quantum ici\n");
        }
    }
    else
        printf("Vous poss�dez d�j� un cube Quantum sur cette plan�te, vous ne pouvez pas effectuer cette action\n");
}


//Sous programme de l'action *Recherche. Permet au joueur d'augmenter la valeur de son d� *Recherche
void Recherche(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage)
{
    printf("Votre D� Recherche augmente de 1\n");
    tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Recherche ++;
    printf("La valeur de votre De Recherche est %d\n", tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Recherche);
    if (tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Recherche == 6)
    {
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination ++;
        printf("Votre D� Domination augmente de 1 et votre D� Recherche revient � 1\n");
        printf("La valeur de votre D� Domination est %d\n", tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Domination);
        Domination(tab_Joueurs, tab_Plateau, NbJ, J1, Passage);
        tab_Joueurs[(J1 + Passage)%NbJ].Cpt_Recherche = 1;
    }
}
