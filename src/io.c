/**
 * \file io.c
 * \brief Ensemles de fonctions qui permettent **l'affichage de la grille et le controle du jeu**\n
 * 		  A l'aide de ce code, on peut: afficher une ligne, une colonne, ainsi qu'une grille complète. Il est également possible d'effacer la grille.
 * \author Bendriss Mohamed Dris **Uniquement pour les commentaires**
 */
#include <stdlib.h>
#include <unistd.h>

#include "io.h"

int vieillsement=0;

void print_gui(int evo, int aging){

	printf("Nombre d'évolutions: %d\n", evo);

	if(aging==0) printf("Vieillsement: Désactivé\n");
	else printf("Vieillsement: Activé\n");

	//if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) printf("Voisinage: Cyclique");
	//else printf("Voisinage: Non Cyclique");

}

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


void affiche_ligne (int c, int* ligne){
	int i;

	for (i=0; i<c; ++i){
		if(vieillsement==1){
			if (ligne[i] <= 0 ) printf ("|   "); else printf ("| %d ", (ligne[i]-1)%10);
		}
		else{
			if (ligne[i] <= 0 ) printf ("|   "); else printf ("| 0 ");
		}
	}
		
	printf("|\n");
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

	int timeEvo=0;
	char c=getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		efface_grille(*g);
		switch (c) {
			case '\n' : 

			{ // touche "entree" pour évoluer
				evolue(g, gc);
				timeEvo++;
				efface_grille(*g);
				system("clear");
				print_gui(timeEvo, vieillsement);
				affiche_grille(*g);
				break;
			}

			case 'n':

			{	affiche_grille(*g);
				printf("Entrez le chemain de la grille: ");
				char grille_name[25];
				scanf(" %s", grille_name);
				efface_grille(*g);
				libere_grille(g);
				libere_grille(gc);
				timeEvo=0;
				system("clear");
				init_grille_from_file(grille_name, g);
				alloue_grille(g->nbl, g->nbc, gc);
				print_gui(timeEvo, vieillsement);
				affiche_grille(*g);
				getchar();
				break;
			}

			case 'v':

			{	
				system("clear");
				if(vieillsement==0) vieillsement=1;
				else vieillsement=0;

				print_gui(timeEvo, vieillsement);
				affiche_grille(*g);
				getchar();
				break;
			}

			case 'c':

			/*{
				if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
				else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;

				system("clear");
				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			}*/

			default :

			{ // touche non traitée
				system("clear");
				print_gui(timeEvo, vieillsement);
				affiche_grille(*g);
				getchar();
				break;

			}

		}
		c = getchar();
		
	}
	return;	
}
