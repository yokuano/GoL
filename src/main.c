/**
 * \file main.c
 * \brief Fonction principale qui permet de **lancer le jeu**
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>


#include "grille.h"
#include "io.h"
#include "jeu.h"

extern int vieillsement;
/**
 * \param[in] argc
 * \param[in] argv
 * \brief Permet de jouer au jeu de la vie
 */
int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	system("clear");
	print_gui(0, vieillsement, compte_voisins_vivants);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
	
}
