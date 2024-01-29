#ifndef OUTILS_H_INCLUDED
#define OUTILS_H_INCLUDED
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

int LancerD();
void color (int couleurDuTexte, int couleurDuFond);
void Domination(S_Joueur tab_Joueurs[], S_Case tab_Plateau[9][9], int NbJ, int J1, int Passage);

#endif // OUTILS_H_INCLUDED
