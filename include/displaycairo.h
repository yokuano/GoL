#ifndef __DISPLAYCAIRO_H
#define __DISPLAYCAIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "jeu.h"

#define SQUARE_SIZE 50

/**
 * \param[in,out] surface
 * \param[in] cr
 * \param[in] g
 * \param[in] debut_ligne_x
 * \param[in] debut_ligne_y
 * \brief Affiche les lignes d'une grille
 */
void print_lignes(cairo_surface_t *surface, cairo_t *cr, grille* g, int debut_ligne_x, int debut_ligne_y);

/**
 * \param[in,out] surface
 * \param[in] cr
 * \param[in] g
 * \param[in,out] debut_colonne_x
 * \param[in,out] debut_colonne_y
 * \brief Affiche les colonnes d'une grille
 */
void print_colonnes(cairo_surface_t *surface, cairo_t *cr, grille* g, int debut_colonne_x, int debut_colonne_y);


/**
 * \param[in,out] surface
 * \param[in] g
 * \brief Affiche la grille g dans la fenettres graphique
 */
void print_grille(cairo_surface_t *surface, grille *g);

#endif