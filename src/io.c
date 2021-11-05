/**
 * \file io.c
 * \brief Ensemles de fonctions qui permettent **l'affichage de et le controle du jeu**
 * \author Bendriss Mohamed Dris
 */
#include <stdlib.h>
#include <unistd.h>

#include "io.h" 


#define BLACK "\x1b[30m" 
#define COL_END "\x1b[0m" 
#define LOG_BLACK(X) printf("%s%s%s",BLACK,X,COL_END)
#define BLUE "\x1b[34m" 
#define BLUE_END "\x1b[0m" 

extern int vieillsement;


void print_gui(int evo, int aging, int (*compte_voisins_vivants) (int, int, grille)){

	system("clear");

	printf("Nombre d'évolutions: %d\n", evo);

	if(aging==0) printf("Vieillissement: Désactivé\n");
	else printf("Vieillissement: Activé\n");

	if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) printf("Voisinage: Cyclique");
	else printf("Voisinage: Non Cyclique");

	printf("\n");

}

void affiche_trait (int c){

	int i;
	for (i=0; i<c; ++i) LOG_BLACK("|---");
	LOG_BLACK("|\n");
	return;

}


void affiche_ligne (int c, int* ligne){

	int i;

	for (i=0; i<c; ++i){

		if(vieillsement==1){
			if (ligne[i] == 0 ) LOG_BLACK("|   ");
			else if (ligne[i] == -1) {LOG_BLACK("|"); printf(" X ");}
			else {
				LOG_BLACK("|"); printf(" %d ", (ligne[i]-1));
			}
		}
		else{
			if (ligne[i] == 0 ) LOG_BLACK("|   "); 
			else if (ligne[i] == -1 ) {LOG_BLACK("|"); printf(" X ");}
			else {
				LOG_BLACK("|"); printf(BLUE " O " BLUE_END);
			}
		}

	}
		
	LOG_BLACK("|\n");
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

			{	evolue(g, gc);
				timeEvo++;
				efface_grille(*g);
				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				break;
			}

			case 'n':

			{	print_gui(timeEvo, vieillsement, compte_voisins_vivants);
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
			}

			case 'v':

			{	if(vieillsement==0) vieillsement=1;
				else vieillsement=0;

				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			}

			case 'c':

			{	if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
				else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;

				print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			}

			default :

			{	print_gui(timeEvo, vieillsement, compte_voisins_vivants);
				affiche_grille(*g);
				getchar();
				break;
			}

		}
		c = getchar();
		
	}
	return;	
}