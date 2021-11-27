/**
 * \file grille.h
 * \brief Bibliothèque contenant les fonctions de grille.c. Permet de manipuller la grille
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/**
 * \struct grille
 * \brief Structure qui représente une grille\n
 * **nbl**: nombre de lignes\n
 * **nbc**: nombre de colonnes\n
 * **cellules**: tableau d'entiers à 2 dimensions\n
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * \param[in] l Nombre de lignes dans la grilles
 * \param[in] c Nombre de colonnes de ma grille
 * \param[out] g Pointeur vers une grille que l'on va allouer en mémoire
 * \brief Alloue une **grille** de taille **l*c**, et initialise **toutes les cellules à mortes**
 */
void alloue_grille (int l, int c, grille* g);

/**
 * \brief **Libère** la grille mise en paramètre de l'espace mémoire
 * \param[out] g Grille que l'on libère de l'éspace mémoire
 */
void libere_grille (grille* g);

/**
 * \param[in] filename Nom du fichier texte de la grille que nous allons charger
 * \param[out] g Grille g
 * \brief **Créer** une grille **à partir d'un fichier** mis en argument filename
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[out] g Grille en cours d'utilisation par le programme
 * \brief Rend **vivante** la cellule (i, j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[out] g Grille en cours d'utilisation par le programme
 * \brief Rend **morte** la cellule (i, j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[out] g Grille en cours d'utilisation par le programme
 * \brief Rend **non viable** la cellule (i, j) de la grille g
 */
static inline void set_nonviable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[in] g Grille en cours d'utilisation par le programme
 * \brief **Teste** si la cellule (i, j) est **vivante**
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j]>=1 && g.cellules[i][j]<=9;}

/**
 * \param[in] i Coordonée i de la cellule
 * \param[in] j Coordonée j de la cellule
 * \param[in] g Grille en cours d'utilisation par le programme
 * \brief **Teste** si la cellule (i, j) est **viable**
 */
static inline int est_viable(int i, int j, grille g){return g.cellules[i][j]!=-1;}


/**
 * \param[in] gs Grille de base
 * \param[out] gd Grille ou l'on mettra le contenue de gs
 * \brief **Copie** la grille **gs** dans la grille **gd**
 */
void copie_grille (grille gs, grille gd);

/**
 * \brief Test si deux grille sont identique ou non (les grilles sont supposé de meme taille)
 * 
 * \param[in] g1 
 * \param[in] g2 
 * \return boolean
 */
bool testEquivalenceGrille(grille* g1, grille* g2);

/**
 * \brief Test si une grille est vide
 * 
 * \param[in] g 
 * \return boolean
 */
bool testVideGrille(grille* g);

#endif
