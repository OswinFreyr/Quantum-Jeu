#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Types structures
//----------------------------------------------------

struct Joueur {
                int Cpt_Domination;
                int Cpt_Recherche;
                int Nb_cubes_Quantum;
                int Nb_Vaisseaux_Casse;
                int Couleur;
                int tab_Vaisseaux[3];
              };
typedef struct Joueur S_Joueur;


struct Case {
                int Couleur;
                int Cubes_Quantum[4];
                int Valeur;
            };
typedef struct Case S_Case;

//----------------------------------------------------
//Prototypes

int LancerD();
void color (int couleurDuTexte, int couleurDuFond);
void Initialisation_Joueur (S_Joueur tab_Joueurs[], int NbJ);
void Initialisation_Joueurs (S_Joueur tab_Joueurs[], int NbJ);
void Initialisation_Plateau (S_Case tab_Plateau[9][9], int NbJ);
void Affichage_Joueur (S_Joueur tab_Joueurs[], int NbJ);
void Affichage_Joueurs (S_Joueur tab_Joueurs[], int NbJ);
void Affichage_Plateau (S_Case tab_Plateau[9][9], int NbJ);
void Initialisation_Vaisseaux (S_Joueur tab_Joueurs[], int NbJ);
void Creation_Vaisseaux (S_Joueur tab_Joueurs[], int i);
void Determination_1er_Joueur (S_Joueur tab_Joueurs[], int NbJ);
void Egalite_2 (S_Joueur tab_Joueurs[], int i, int j);
void Egalite_3 (S_Joueur tab_Joueurs[], int i, int j, int k);
void Egalite_4 (S_Joueur tab_Joueurs[], int i, int j, int k, int l);
void Deploiement_Vaisseaux ();
void Affichage_Vaisseaux_Depart ();


//----------------------------------------------------
int main()
{
    printf("Bienvenue au jeu Quantum\n\n");
    printf("Combien de joueurs veulent jouer a Quantum ?\n");
    int NbJ;
    scanf("%d", &NbJ);
    S_Joueur *tab_Joueurs = NULL;
    tab_Joueurs = malloc(sizeof(S_Joueur) * NbJ);
    if(tab_Joueurs == NULL)
    exit(1);
    Initialisation_Joueurs (tab_Joueurs, NbJ);
    Affichage_Joueurs (tab_Joueurs, NbJ);
    S_Case tab_Plateau[9][9];
    Initialisation_Plateau (tab_Plateau, NbJ);
    Affichage_Plateau (tab_Plateau, NbJ);
    Initialisation_Vaisseaux (tab_Joueurs, NbJ);
    Determination_1er_Joueur (tab_Joueurs, NbJ);
    Deploiement_Vaisseaux ();
    Affichage_Vaisseaux_Depart ();

    free(tab_Joueurs);
    return 0;
}

//----------------------------------------------------
//Sous-program

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


void color (int couleurDuTexte, int couleurDuFond)
{
     HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
}


void Initialisation_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    tab_Joueurs[NbJ].Cpt_Domination = 1;
    tab_Joueurs[NbJ].Cpt_Recherche = 1;
    tab_Joueurs[NbJ].Nb_cubes_Quantum = 5;
    tab_Joueurs[NbJ].Nb_Vaisseaux_Casse = 2;
    if (NbJ == 0)
        tab_Joueurs[NbJ].Couleur = 11;
    if (NbJ == 1)
        tab_Joueurs[NbJ].Couleur = 12;
    if (NbJ == 2)
        tab_Joueurs[NbJ].Couleur = 10;
    if (NbJ == 3)
        tab_Joueurs[NbJ].Couleur = 14;
}


void Initialisation_Joueurs (S_Joueur tab_Joueurs[], int NbJ)
{
    int i;
    for (i = 0; i < NbJ; i ++)
    {
        Initialisation_Joueur(tab_Joueurs, i);
    }
}


void Affichage_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    printf("La valeur de votre De Domination est %d\n", tab_Joueurs[NbJ].Cpt_Domination);
    printf("La valeur de votre De Recherche est %d\n", tab_Joueurs[NbJ].Cpt_Recherche);
    printf("Vous possedez %d cubes Quantum\n", tab_Joueurs[NbJ].Nb_cubes_Quantum);
    printf("Vous avez %d Vaisseaux dans votre casse\n\n\n", tab_Joueurs[NbJ].Nb_Vaisseaux_Casse);
}


void Affichage_Joueurs (S_Joueur tab_Joueurs[], int NbJ)
{
    int i;
    for (i = 0; i < NbJ; i ++)
    {
        color(tab_Joueurs[i].Couleur,0);
        Affichage_Joueur (tab_Joueurs, i);
        color (15,0);
    }
}


void Initialisation_Plateau (S_Case tab_Plateau[9][9], int NbJ)
{
    int i; int j;
    if (NbJ == 2)
    {
        for(i = 0; i < 9; i ++)
        {
            for(j = 0; j < 9; j ++)
            {
                tab_Plateau[i][j].Valeur = 0;
            }
        }
        tab_Plateau[1][1].Valeur = 7; tab_Plateau[4][1].Valeur = 7; tab_Plateau[7][1].Valeur = 7; tab_Plateau[1][4].Valeur = 7; tab_Plateau[1][7].Valeur = 7; tab_Plateau[4][7].Valeur = 7; tab_Plateau[7][7].Valeur = 7;
        tab_Plateau[4][4].Valeur = 8; tab_Plateau[7][4].Valeur = 8;
    }
    if (NbJ == 3)
    {
        for(i = 0; i < 9; i ++)
        {
            for(j = 0; j < 9; j ++)
            {
                tab_Plateau[i][j].Valeur = 0;
            }
        }
        tab_Plateau[1][1].Valeur = 7; tab_Plateau[1][7].Valeur = 7; tab_Plateau[7][4].Valeur = 7;
        tab_Plateau[4][1].Valeur = 8; tab_Plateau[7][1].Valeur = 8; tab_Plateau[1][4].Valeur = 8; tab_Plateau[4][7].Valeur = 8; tab_Plateau[7][7].Valeur = 8;
        tab_Plateau[4][4].Valeur = 9;
    }
    if (NbJ == 4)
    {
        for(i = 0; i < 9; i ++)
        {
            for(j = 0; j < 9; j ++)
            {
                tab_Plateau[i][j].Valeur = 0;
            }
        }
        tab_Plateau[1][1].Valeur = 8; tab_Plateau[4][1].Valeur = 8; tab_Plateau[7][4].Valeur = 8; tab_Plateau[1][7].Valeur = 8; tab_Plateau[4][7].Valeur = 8;
        tab_Plateau[7][1].Valeur = 9; tab_Plateau[1][4].Valeur = 9; tab_Plateau[7][7].Valeur = 9;
        tab_Plateau[4][4].Valeur = 10;
    }
}


void Affichage_Plateau (S_Case tab_Plateau[9][9], int NbJ)
{
    int i; int j;
    if (NbJ == 2 || NbJ == 3)
    for(i = 0; i < 9; i ++)
    {
        for(j = 0; j < 9; j ++)
        {
                if (tab_Plateau[i][j].Valeur > 6)
                    color (13,0);
                printf(" %d ", tab_Plateau[i][j].Valeur);
                color (15,0);
        }
        printf("\n");
    }
    if (NbJ == 4)
    {
        for(i = 0; i < 9; i ++)
        {
            for(j = 0; j < 9; j ++)
            {
                if (tab_Plateau[i][j].Valeur > 6)
                    color (13,0);
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


void Initialisation_Vaisseaux(S_Joueur tab_Joueurs[], int NbJ)
{
    int Choix = 0;
    for (int i = 0; i < NbJ; i++)
    {
        printf("On initialise les vaisseaux du Joueur %d\n", i+1);
        Creation_Vaisseaux(tab_Joueurs, i);
        printf("Etes vous satisfait de votre lancer ? (1.Oui  2.Non)\n");
        do
        {
            scanf("%d", &Choix);
            if (Choix != 1 && Choix != 2) printf("No. Invalide\n");
        }while(Choix !=1 && Choix != 2);
        if(Choix == 2) Creation_Vaisseaux(tab_Joueurs, i);
    }
}


void Creation_Vaisseaux(S_Joueur tab_Joueurs[], int i)
{
     for (int j = 0; j < 3; j++)
     {
             tab_Joueurs[i].tab_Vaisseaux[j] = LancerD();
             printf("Ton vaisseau no. %d a pour valeur %d \n", j+1, tab_Joueurs[i].tab_Vaisseaux[j]);
     }
}


void Determination_1er_Joueur (S_Joueur tab_Joueurs[], int NbJ)
{
    int i; int j; int k; int l;
    if (NbJ == 2)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        if (i > j)
        {
            printf("Le joueur rouge est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
        }
        if (i < j)
        {
            printf("Le joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
        }
        if (i == j)
            Egalite_2 (tab_Joueurs, i, j);
    }
    if (NbJ == 3)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        k = tab_Joueurs[2].tab_Vaisseaux[0] + tab_Joueurs[2].tab_Vaisseaux[1] + tab_Joueurs[2].tab_Vaisseaux[2];
        if (j < i && j < k)
        {
            printf("Le joueur rouge est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
        }
        if (i < j && i < k)
        {
            printf("Le joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
        }
        if (k < i && k < j)
        {
            printf("Le joueur vert est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur rouge est le joueur 3\n");
        }
        if (i == j && i < k)
            Egalite_3 (tab_Joueurs, i, j, k);
        if (i == k && i < j)
            Egalite_3 (tab_Joueurs, i, j, k);
        if (j == k && j < i)
            Egalite_3 (tab_Joueurs, i, j, k);
    }
    if (NbJ == 4)
    {
        i = tab_Joueurs[0].tab_Vaisseaux[0] + tab_Joueurs[0].tab_Vaisseaux[1] + tab_Joueurs[0].tab_Vaisseaux[2];
        j = tab_Joueurs[1].tab_Vaisseaux[0] + tab_Joueurs[1].tab_Vaisseaux[1] + tab_Joueurs[1].tab_Vaisseaux[2];
        k = tab_Joueurs[2].tab_Vaisseaux[0] + tab_Joueurs[2].tab_Vaisseaux[1] + tab_Joueurs[2].tab_Vaisseaux[2];
        l = tab_Joueurs[3].tab_Vaisseaux[0] + tab_Joueurs[3].tab_Vaisseaux[1] + tab_Joueurs[3].tab_Vaisseaux[2];
        if (i < j && i < k && i < l)
        {
            printf("Le joueur bleu est le joueur 1\n");
            printf("Le joueur rouge est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
            printf("Le joueur jaune est le joueur 4\n");
        }
        if (j < i && j < k && j < l)
        {
            printf("Le joueur rouge est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur vert est le joueur 3\n");
            printf("Le joueur jaune est le joueur 4\n");
        }
        if (k < i && k < j && k < l)
        {
            printf("Le joueur vert est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur rouge est le joueur 3\n");
            printf("Le joueur jaune est le joueur 4\n");
        }
        if (l < i && l < j && l < k)
        {
            printf("Le joueur jaune est le joueur 1\n");
            printf("Le joueur bleu est le joueur 2\n");
            printf("Le joueur rouge est le joueur 3\n");
            printf("Le joueur vert est le joueur 4\n");
        }
        if (i == j && i < k && i < l)
            Egalite_4 (tab_Joueurs, i, j, k, l);
        if (i == k && i < j && i < l)
            Egalite_4 (tab_Joueurs, i, j, k, l);
        if (i == l && i < j && i < k)
            Egalite_4 (tab_Joueurs, i, j, k, l);
        if (j == k && j < i && j < l)
            Egalite_4 (tab_Joueurs, i, j, k, l);
        if (j == l && j < i && j < k)
            Egalite_4 (tab_Joueurs, i, j, k, l);
        if (k == l && k < i && k < i)
            Egalite_4 (tab_Joueurs, i, j, k, l);
    }
}


void Egalite_2 (S_Joueur tab_Joueurs[], int i, int j)
{
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
}


void Egalite_3 (S_Joueur tab_Joueurs[], int i, int j, int k)
{
    if(j==k&&j<i)
        {
            int D1;
            int D2;
            int D3;
            int D4;
            int R1;
            int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
        if(i==j&&i<k)
        {
            int D1;
            int D2;
            int D3;
            int D4;
            int R1;
            int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
        if(i==k&&i<j)
        {
            int D1;
            int D2;
            int D3;
            int D4;
            int R1;
            int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
    }


void Egalite_4 (S_Joueur tab_Joueurs[], int i, int j, int k, int l)
{
    if(j==k&&j<i&&j<l)
        {
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
        if(i==l&&i<j&&i<k)
        {
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
        if(i==j&&i<k&&i<l)
        {
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
         if(i==k&&i<j&&i<l)
        {
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
        if(j==l&&j<i&&j<k)
        {
        int D1;
        int D2;
        int D3;
        int D4;
        int R1;
        int R2;
            do
            {
                printf("Les joueurs relancent chacun deux des pour les departager \n");
                D1=LancerD();
                printf("%d\t", D1);
                D2=LancerD();
                printf("%d\n\n", D2);
                D3=LancerD();
                printf("%d\t", D3);
                D4=LancerD();
                printf("%d\n\n", D4);
                R1=D1+D2;
                R2=D3+D4;
                printf("Le premier joueur qui a relance les des a obtenu : %d\n", R1);
                printf("Le deuxieme joueur qui a relance les des a obtenu : %d\n", R2);
                if (R1>R2)
                {
                    printf("Le deuxieme joueur qui a relancer ses vaisseaux est le joueur 1\n");
                    printf("Le premier joueur qui a relancer ses vaisseaux est le joueur 2\n");
                }
                else
                {
                    printf("Le premier joueur qui a rentre ses vaisseaux est le joueur 1\n");
                    printf("Le second joueur qui a rentre ses vaisseaux est le joueur 2\n");
                }
            }while(R1 == R2);
        }
}


void Deploiement_Vaisseaux ()
{

}


void Affichage_Vaisseaux_Depart ()
{

}
