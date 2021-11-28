/**
 * \file io.h
 * \brief Bibliothèque contenant les fonctions de io.c.\n Permet d'afficher le jeu sur le terminal et d'actualisé l'affichage.
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#ifndef __IO_H
#define __IO_H

#include "grille.h"
#include "jeu.h"

/**
 * \param[in] evo
 * \param[in] aging
 * \param[in] compre_voisin_vivant
 * \brief Affiche les paramètres actuel de la grille 
 */
void print_gui(int evo, int aging, int (*compte_voisins_vivants) (int, int, grille));


/**
 * \param[in] c
 * \brief Affiche en console le motif "|---" **c fois**. 
 */
// affichage d'un trait horizontal
void affiche_trait (int c);

/**
 * \param[in] c
 * \param[out] ligne
 * \brief Stock une chaine de charactère **contenant le charactère "|" c fois**, ainsi qu'un **saut a la ligne entre chaque charactère**. Permet d'afficher une ligne\n
 */
void affiche_ligne (int c, int* ligne);

/**
 * \param[out] g
 * \brief Permet d'affiche une grille
 */
void affiche_grille (grille g);

/**
 * \param[out] g
 * \brief Permet d'effacer une grille
 */
void efface_grille (grille g);

/**
 * \param[in, out] g
 * \param[in, out] gc
 * \brief Permet de commencer le jeux:\n
 * -Si on appuie sur la touche **Enter**: on passe à **l'état suivant de la grille**.\n
 * -Si on appuie sur la touche **Q**: on **arrete le jeu**.\n
 * -Si on appuie sur la touche **N**: on peux **activer/désactiver** le vieillsement
 * -Si on appuie sur la touche **C**: on peux **activer/désactiver** le voisinage cycliquer
 * -Si on appuie sur la touche **O**: on peux **lancer un teste d'oscillation**
 * -Si on appuie sur **une autre touche**: on **efface le charactère**, et rien ne se passe
 */
void debut_jeu(grille *g, grille *gc);

#endif

