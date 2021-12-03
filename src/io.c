/**
 * \file io.c
 * \brief Ensemles de fonctions qui permettent **l'affichage de et le controle du jeu**
 * \author Bendriss Mohamed Dris
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <unistd.h>

#include "io.h" 


#define BLACK "\x1b[30m" 			// Color for the grid
#define RED "\x1b[31m" 				// Color for cell that cannot develop life
#define BLUE "\x1b[34m"  			// Color for cells when aging is disabled
#define GREEN "\x1b[32m" 			// Color for the cells when aging is enabled
#define COL_END "\x1b[0m"			// Used to stop the color change (rest color to default)

#define LOG_COLOR(string, color) printf("%s%s%s",color, string, COL_END) // Prints the string in the color passed as argument 
#define LOG_COLOR_INTEGER(int, color) printf(color " %d " COL_END, int) // Prints the INTEGER int in the color passed as argument

extern int vieillsement;
extern int timeEvo;

void print_gui(int evo, int aging, int (*compte_voisins_vivants) (int, int, grille)){

	system("clear");																						// Netoyage du terminal

	printf("Nombre d'évolutions: %d\n", evo);																// Affichage nb evo

	if(aging==0) printf("Vieillissement: Désactivé\n");														// Affichage vieillssement
	else printf("Vieillissement: Activé\n");

	if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) printf("Voisinage: Cyclique");		// Affichage mode cyclique ou non cyclique
	else printf("Voisinage: Non Cyclique");

	printf("\n");

}

void affiche_trait (int c){

	int i;
	for (i=0; i<c; ++i) 
		LOG_COLOR("|---", BLACK);
	LOG_COLOR("|\n", BLACK);
	return;

}


void affiche_ligne (int c, int* ligne){

	int i;

	for (i=0; i<c; ++i){

		if(vieillsement==1){										// Vieillsement activé

			if (ligne[i] == 0 ) 										// Cas d'une cellule morte
				LOG_COLOR("|   ", BLACK); 								
			else if (ligne[i] == -1) {									// Cas d'une cellule non viable
				LOG_COLOR("|", BLACK); 
				LOG_COLOR(" X ", RED);}											
			else {														// Cas d'une cellule vivante
				LOG_COLOR("|", BLACK); 
				LOG_COLOR_INTEGER(ligne[i]-1, GREEN);				
			}

		}

		else{														// Vieillsement désactivé

			if (ligne[i] == 0 ) 										// Cas d'une cellule morte
				LOG_COLOR("|   ", BLACK); 								
			else if (ligne[i] == -1 ) {									// Cas d'une cellule non viable
				LOG_COLOR("|", BLACK); 									
				LOG_COLOR(" X ", RED);}									
			else {														// Cas d'une cellule morte
				LOG_COLOR("|", BLACK); 
				LOG_COLOR(" O ", BLUE);					
			}

		}

	}
		
	LOG_COLOR("|\n", BLACK);
	return;
}

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


void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){

	char c=getchar();

	while (c != 'q') // touche 'q' pour quitter
	{
		efface_grille(*g);
		switch (c) {

			case '\n' : 

				evolue(g, gc);
				timeEvo++;
				efface_grille(*g);
				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				break;
			
			case 'n':

				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g); //afficher la grille pour éviter les overlap d'affichage
				printf("Entrez le chemain de la grille: ");

				char grille_name[25];
				scanf(" %s", grille_name);
				efface_grille(*g);
				libere_grille(g);
				libere_grille(gc);

				timeEvo=0;
				init_grille_from_file(grille_name, g);
				alloue_grille(g->nbl, g->nbc, gc);
				
				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			

			case 'v':

				if(vieillsement==0) vieillsement=1;
				else vieillsement=0;

				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			

			case 'c':

				if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
				else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;

				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;

			case 'o':
				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				int res=calcul_oscillation_wrapper(g, gc);
				printf("Osscillation de cette grille: %d", res);
				getchar();
				break;
			default :
				getchar();
				break;
		}
		c = getchar();
		
	}
	return;	
}