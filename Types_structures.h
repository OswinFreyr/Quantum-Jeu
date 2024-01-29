#ifndef TYPES_STRUCTURES_H_INCLUDED
#define TYPES_STRUCTURES_H_INCLUDED


//Type structuré pour le joueur qui contient les données propres à chaque joueur
struct Joueur {
                int Cpt_Domination;
                int Cpt_Recherche;
                int Nb_cubes_Quantum;
                int Nb_Vaisseaux_Casse;
                int Couleur;
                int tab_Vaisseaux[3];
              };
typedef struct Joueur S_Joueur;


//Type structuré pour la case qui contient les données propres à chaque case du plateau de jeu
struct Case {
                int Couleur;
                int Cubes_Quantum[4];
                int Nb_Cubes_Quantum;
                int Valeur;
                int Num_Vaisseaux[4][3];
            };
typedef struct Case S_Case;


#endif // TYPES_STRUCTURES_H_INCLUDED
