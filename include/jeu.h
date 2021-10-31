/**
 * \file jeu.h
 * \brief Bibliothèque contenant les fonctions de jeu.c
 * \author Bendriss Mohamed Dris
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \param[in] i
 * \param[in] j
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \return (i+m)%m
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \param[in] i
 * \param[in] j
 * \param[in] g
 * \brief Permet de compter **les cellules voisines** de la cellules de coordonnées (i, j) en mode cyclique
 * \return Nombre de voisins v (int) en mode cyclique
 */
int compte_voisins_vivants_en_mode_cyclique(int i, int j, grille g);

/**
 * \param[in] i
 * \param[in] j
 * \param[in] g
 * \brief Permet de compter **les cellules voisines** de la cellules de coordonnées (i, j) en mode non cyclique
 * \return Nombre de voisins v (int) en mode non cyclique
 */
int compte_voisins_vivants_en_mode_non_cyclique(int i,int j,grille g);

/**
 * \param[in] i
 * \param[in] j
 * \param[in, out] g
 * \brief Permet de calculer l'age d'une cellule à l'état t+1
 */
void calcul_vieillissement(grille *g);

/**
 * \param[in, out] g
 * \param[out] gc
 * \brief Fait **évolué** la grille g
 */
void evolue (grille *g, grille *gc);

/**
 * \brief Pointeur de fonction qui pointera sur l'une des fonctions de calcul de voisinage selon si le mode choisi est cyclique ou non
 */
int (*compte_voisins_vivants) (int, int, grille);

#endif

