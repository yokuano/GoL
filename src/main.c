/**
 * \file main.c
 * \brief Fonction principale qui permet de **lancer le jeu**
 * \author Bendriss Mohamed Dris **uniquement pour les fonctions allouer_grille et libere grille**
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

extern int vieillissement;
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
	print_gui(0, 0, compte_voisins_vivants);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
