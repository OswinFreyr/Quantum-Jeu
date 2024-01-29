#ifndef CAPACITES_SPECIALES_H_INCLUDED
#define CAPACITES_SPECIALES_H_INCLUDED


void Station_de_Combat(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);
void Vaisseau_Amiral(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);
void Voyage(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage, int i, int j, int z, int m);
void Destroyer(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);
void Fregate(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);
void Eclaireur(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);


#endif // CAPACITES_SPECIALES_H_INCLUDED
