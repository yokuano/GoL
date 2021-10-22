#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \param[in] i
 * \param[out] j
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \return (i+m)%m
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants_en_mode_cyclique(int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont non cyclique
int compte_voisins_vivants_en_mode_non_cyclique(int i,int j,grille g);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
