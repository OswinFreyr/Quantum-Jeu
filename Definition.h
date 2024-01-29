#define DEFINITION_H_INCLUDED


//Types structures
//---------------------------------------------
struct Joueur {
                int Cpt_Domination;
                int Cpt_Recherche;
                int Nb_cubes_Quantum;
                int Nb_Vaisseaux_Casse;
                int Couleur;
              };
typedef struct Joueur S_Joueur;


struct Case {
                int Couleur;
                int Cubes_Quantum[5];
            };
typedef struct Case S_Case;
