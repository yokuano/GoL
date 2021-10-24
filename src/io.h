#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"


void print_gui(int evo, int aging);


/**
 * \param[in] c
 * \brief Affiche en console le motif "|---" **c fois**. Par exemple, avec **c=5**, on obitient:\n |---|---|---|---|---|
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
 * \brief Permet d'affiche la grille g
 */
void affiche_grille (grille g);

/**
 * \param[out] g
 * \brief Permet d'effacer la grille g
 */
void efface_grille (grille g);

/**
 * \param[out] g
 * \param[out] gc
 * \brief Permet de commencer le jeux:\n
 * -Si on appuie sur la touche **Enter**: on passe à **l'état suivant de la grille**.\n
 * -Si on appuie sur la touche **Q**: on **arrete le jeu**.\n
 * -Si on appuie sur **une autre touche**: on **efface le charactère**, et rien ne se passe
 */
void debut_jeu(grille *g, grille *gc);

#endif
