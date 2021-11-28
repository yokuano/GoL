/**
 * \file displaycairo.h
 * \brief Bibliothèque contenant l'ensemble des fonction de displaycairo.c.\n Permet d'afficher et d'actualiser la fenêtre graphique
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef __DISPLAYCAIRO_H
#define __DISPLAYCAIRO_H

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <string.h>
#include <X11/keysymdef.h>
#include <stdbool.h>
#include "io.h"

/** @brief Taille d'une cellule de la grille */
#define SQUARE_SIZE 50
/** @brief Taille de l'interface superieur */
#define GUI_Y 100
/** @brief Change la couleur des actions cairo en blanc */
#define SET_SOURCE_WHITE(cr) cairo_set_source_rgb(cr, 1, 1, 1)
/** @brief Change la couleur des actions cairo en blanc */
#define SET_SOURCE_BLACK(cr) cairo_set_source_rgb(cr, 0, 0, 0)
/** @brief Change la couleur des actions cairo en blanc */
#define SET_SOURCE_GREEN(cr) cairo_set_source_rgb(cr, 0.69019, 0.94901, 0.71372)
/** @brief Change la couleur des actions cairo en blanc */
#define SET_SOURCE_RED(cr) cairo_set_source_rgb(cr, 0.94901, 0.38742, 0.41531)
/** @brief Change la couleur des actions cairo en blanc */
#define SET_SOURCE_GREY(cr) cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
/** @brief Recupere le keycode X11 du character mis en argument */
#define keycode(c) XKeysymToKeycode(dpy, XStringToKeysym(c))
extern int darkmode;

/**
 * \brief Concaténe la chaine s1 et s2 en une nouvelle chaine
 * 
 * \param[in] s1 
 * \param[in] s2 
 * 
 * \author David Heffernan on: https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c/8465083#8465083
 * \copyright Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0)
 * \return char* (s1+s2)  
 */
char* concat(const char *s1, const char *s2);


/**
 * brief Permet de trouver le chemain de la grille en fonction de la touche numérique entrée
 * 
 * \param[in] event 
 * \return Tableau de char qui contient le chemain de la grille que l'on veux charger
 */
char* newGrille(int event);


/**
 * \brief Permet d'obtenir la longeure de l'ecran
 * 
 * \return int: Longueur de l'ecran
 */
int getX_SizeWindow();


/**
 * \brief Permet d'obtenir la hauteur de l'ecran
 * 
 * \return int: Hauteur de l'ecran
 */
int getY_SizeWindow();


/**
 * \brief Permet de d'afficher un rectangle dans la fenètre. Le coin gauche du rectangle est de coordonée (debutx, debuty). Les dimmensions du rectangles sont x et y
 * 
 * \param[in, out] cr Cairo Mask
 * \param[in] debutx Coordonée X du point superieur gauche du rectangle
 * \param[in] debuty Coordonée Y du point superieur gauche du rectangle
 * \param[in] x Longueur du rectangle
 * \param[in] y Largeur Y du rectangle
 * \param[in] bold Epaisseur du trait en nombre de pixels
 */
void printRectangle(cairo_t *cr, int debutx, int debuty, int x, int y, int bold);


/**
 * \brief Affiche les lignes d'une grille
 * 
 * \param[in,out] surface surface_cairo
 * \param[in,out] cr Cairo Mask
 * \param[in,out] g Grille g que l'on va afficher
 * \param[in] debut_ligne_x Coordonées X de notre position de base, la ou le tracé commence
 * \param[in] debut_ligne_y Coordonées Y de notre position de base, la ou le tracé commence
 */
void print_lignes(cairo_t *cr, grille* g, int debut_ligne_x, int debut_ligne_y, int squaresize);


/**
 * \brief Affiche les colonnes d'une grille
 * 
 * \param[in,out] surface surface_cairo
 * \param[in,out] cr Cairo Mask
 * \param[in] g Grille g que l'on va afficher
 * \param[in] debut_colonne_x Coordonées X de notre position de base, la ou le tracé commence
 * \param[in] debut_colonne_y Coordonées Y de notre position de base, la ou le tracé commence
 */
void print_colonnes(cairo_t *cr, grille* g, int debut_colonne_x, int debut_colonne_y,  int squaresize);


/**
 * \brief Affiche la zone du GUI consacré au vileillsement
 * 
 * \param[in] vieillsement Vaut 1 si le vieillsement est activé, 0 si il est désactivé
 * \param[in,out] surface surface_cairo
 * \param[in] sizeX Longeur de l'ecran
 * \param[in] sizeY Largeur de l'ecran
 */
void print_GUI_vieillsement(int vieillsement, cairo_surface_t *surface, int sizeX, int sizeY);


/**
 * \brief Affiche la zone du GUI à la grille que l'on charge
 * 
 * \param[in,out] surface surface_cairo
 * \param[in] sizeX Longeur de l'ecran
 * \param[in] sizeY Largeur de l'ecran
 */
void print_GUI_grille(cairo_surface_t *surface, int sizeX, int sizeY);


/**
 * \brief Affiche la zone du GUI consacré au mode de voisinage
 * 
 * \param[in] compte_voisins_vivants Pointeur de fonction sur la fonction qui calcul le nombre de voisins
 * \param[in,out] surface surface_cairo
 * \param[in] sizeX Longeur de l'ecran
 * \param[in] sizeY Largeur de l'ecran
 */
void print_GUI_cycle(int (*compte_voisins_vivants) (int, int, grille), cairo_surface_t *surface, int sizeX, int sizeY);


/**
 * \brief Remplie les cellules de la grille selon leur etat: vivante, non viable, morte
 * 
 * \param[in, out] surface surface_cairo
 * \param[in] g grille g que l'on affiche
 * \param[in] debutTabX Coordonée X du coin en haut a gauche de la grille
 * \param[in] debutTabY Coordonée Y du coin en haut a gauche de la grille
 */
void print_grille(cairo_surface_t *surface, grille *g, int debutTabX, int debutTabY,  int squaresize);


/**
 * @brief Affiche les controles du jeu à gauche de l'écran
 * 
 * \param[in] surface 
 */
void print_crtl(cairo_surface_t *surface);


/**
 * \brief Affiche le resultat du test d'oscillation ainsi que des informations que le motif de grille oscillante à droite de l'ecran
 * 
 * \param[in, out] surface 
 * \param[in] g 
 * \param[in] gc 
 */
void print_oscillation(cairo_surface_t* surface, grille* g, grille* gc);


/**
 * \brief Affiche la totalité de l'interface graphique
 * 
 * \param[in, out] surface cairo_surface 
 * \param[in] g grille g que l'on affiche
 */
void print_GraphicUserInterface(cairo_surface_t *surface, grille *g);


/**
 * \brief Changer la couleur du fond en fonction du mode nuit/jour
 * 
 * \param[in,out] cr 
 */
static inline void set_bg(cairo_t* cr){
    if(darkmode) SET_SOURCE_GREY(cr);
    if(!darkmode) SET_SOURCE_WHITE(cr);   
}


/**
 * \brief Permet de commencer le jeu en version cairo
 * 
 * \param[in,out] g 
 * \param[in,out] gc 
 */
void debut_jeu_cairo(grille *g, grille *gc);

#endif