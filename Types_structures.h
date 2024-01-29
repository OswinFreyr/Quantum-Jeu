#ifndef TYPES_STRUCTURES_H_INCLUDED
#define TYPES_STRUCTURES_H_INCLUDED


//Type structur� pour le joueur qui contient les donn�es propres � chaque joueur
struct Joueur {
                int Cpt_Domination;
                int Cpt_Recherche;
                int Nb_cubes_Quantum;
                int Nb_Vaisseaux_Casse;
                int Couleur;
                int tab_Vaisseaux[3];
              };
typedef struct Joueur S_Joueur;


//Type structur� pour la case qui contient les donn�es propres � chaque case du plateau de jeu
struct Case {
                int Couleur;
                int Cubes_Quantum[4];
                int Nb_Cubes_Quantum;
                int Valeur;
                int Num_Vaisseaux[4][3];
            };
typedef struct Case S_Case;


#endif // TYPES_STRUCTURES_H_INCLUDED
