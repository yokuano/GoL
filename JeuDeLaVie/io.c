/**
 * \file io.c
 * \brief Ensemles de fonctions qui permettent **l'affichage de la grille**\n
 * 		  A l'aide de ce code, on peut: afficher une ligne, une colonne, ainsi qu'une grille complète. Il est également possible d'effacer la grille.
 * \author Bendriss Mohamed Dris **Uniquement pour les commentaires**
 */
#include "io.h"

/**
 * \param[in] c
 * \brief Affiche en console le motif "|---" **c fois**. Par exemple, avec **c=5**, on obitient:\n |---|---|---|---|---|
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * \param[in] c
 * \param[out] ligne
 * \brief Stock une chaine de charactère **contenant le charactère "|" c fois**, ainsi qu'un **saut a la ligne entre chaque charactère**. Permet d'afficher une ligne\n
 * Par exemple si c=3, on affichera:\n
 * |\n
 * |\n
 * |
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

/**
 * \param[out] g
 * \brief Permet d'affiche la grille g
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * \param[out] g
 * \brief Permet d'effacer la grille g
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * \param[out] g
 * \param[out] gc
 * \brief Permet de commencer le jeux:\n
 * -Si on appuie sur la touche **Enter**: on passe à **l'état suivant de la grille**.\n
 * -Si on appuie sur la touche **Q**: on **arrete le jeu**.\n
 * -Si on appuie sur **une autre touche**: on **efface le charactère**, et rien ne se passe
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
