/**
 * \file grille.h
 * \brief Bibliothèque contenant les fonctions de grille.c
 * \author Bendriss Mohamed Dris
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct grille
 * \brief Structure qui représente une grille\n
 * **nbl**: nombre de lignes\n
 * **nbc**: nombre de colonnes\n
 * **cellules**: tableau d'entiers à 2 dimensions\n
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * \param[in] l 
 * \param[in] c
 * \param[out] g
 * \brief Alloue une **grille** de taille **l*c**, et initialise **toutes les cellules à mortes**
 */
void alloue_grille (int l, int c, grille* g);

/**
 * \brief **Libère** la grille mise en paramètre de l'espace mémoire
 * \param[out] g
 */
void libere_grille (grille* g);

/**
 * \param[in] filename
 * \param[out] g
 * \brief **Créer** une grille **à partir d'un fichier** mis en argument filename
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * \param[in] i
 * \param[in] j
 * \param[out] g
 * \brief Rend **vivante** la cellule (i, j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \param[in] i
 * \param[in] j
 * \param[out] g
 * \brief Rend **morte** la cellule (i, j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * \param[in] i
 * \param[in] j
 * \param[in] g
 * \brief **Teste** si la cellule (i, j) est **vivante**
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

/**
 * \param[in] gs
 * \param[out] gd
 * \brief **Copie** la grille **gs** dans la grille **gd**
 */
void copie_grille (grille gs, grille gd);

#endif
