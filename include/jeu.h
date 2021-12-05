/**
 * \file jeu.h
 * \brief Bibliothèque contenant les fonctions de jeu.c.\n Permet de faire évoluer le cours du jeu
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
extern int generationOscillante;

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \return int: (i+m)%m
 */
static inline int modulo(int i, int m) {return (i+m)%m;}


/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[in] g Grille en cours d'utilisation par le programme
 * \brief Permet de compter **les cellules voisines** de la cellules de coordonnées (i, j) en mode cyclique
 * \return int: Nombre de voisins v en mode cyclique
 */
int compte_voisins_vivants_en_mode_cyclique(int i, int j, grille g);


/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[in] g Grille en cours d'utilisation par le programme
 * \brief Permet de compter **les cellules voisines** de la cellules de coordonnées (i, j) en mode non cyclique
 * \return int: Nombre de voisins v en mode non cyclique
 */
int compte_voisins_vivants_en_mode_non_cyclique(int i,int j,grille g);


/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[in,out] g Pointeur vers la grille en cours d'utilisation par le programme
 * \brief Permet de calculer l'age d'une cellule à l'état t+1
 */
void calcul_vieillissement(grille *g);


/**
 * \param[in, out] g Pointeur vers une grille rille en cours d'utilisation par le programme
 * \param[out] gc Pointeur vers une grille dans laquelle on copie le contenue de la grille g
 * \brief Fait **évolué** la grille g
 */
void evolue (grille *g, grille *gc);


/**
 * \brief Pointeur de fonction qui pointera sur l'une des fonctions de calcul de voisinage selon si le mode choisi est cyclique ou non
 */
int (*compte_voisins_vivants) (int, int, grille);


/**
 * \brief Permet de calculer l'oscillation d'une colonie à partir d'une certaine position de base
 * 
 * \param[in,out] g 
 * \return int oscillation d'une grille à un etat n unique (limité à vérifier jusqu'à 512 générations)
 */
int calcul_oscillation(grille *g);


/**
 * \brief Permet de calculer l'oscillation d'une colonie, en prenant en compte le fait que la colonie passé en argument ne soit pas forcement un motif oscillant dans l'imediat
 * 
 * \param[in, out] g 
 * \param[in, out] gc 
 * \return int oscillation d'une grille à partir d'un certain etat (limité à 512 testes, donc peut aller jusqu'a la génération 1024)
 */
int calcul_oscillation_wrapper(grille *g, grille *gc);


/**
 * \brief Assigner la valeur par defaut à la génération oscillante une fois le calcul de l'oscillation terminé
 * 
 */
static inline void setGen(){generationOscillante=1;}

#endif

