/**
 * @file cairomain.c
 * @author Bendriss Mohamed Dris
 * @brief Fichier main qui permet de lancer le jeux en mode graphique 
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "displaycairo.h"

extern int vieillsement;
extern int timeEvo;
extern int darkmode; 


int main (int argc, char ** argv){

	if (argc != 2 )
	{
		printf("usage : ./bin/cairomain <fichier grille>");
		return 1;
	}
    grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	debut_jeu_cairo(&g, &gc);
		
}