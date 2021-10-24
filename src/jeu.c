/**
 * \file jeu.c
 * \brief Ensembles de fonctions permettant de **faire avancer le cours du jeu**
 * \author Bendriss Mohamed Dris **uniquement la doccumentation**
 */

#include "jeu.h"

int cyclique=1;

int compte_voisins_vivants_en_mode_cyclique(int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_en_mode_non_cyclique(int i,int j,grille g){
	int v=0;
	int l=g.nbl; 
	int c=g.nbc;

	for(int n=i-1; n<=i+1; i++){
		for(int m=j-1; j<=j+1; j++){

			if ( ( n>=0 && n<=l ) && ( m>=0 && m<=c ) )
			{
				v=v+est_vivante(n, m, g);
			}
		
		}
	}

	return v;
}

void calcul_vieillissement(grille *g){

	for(int i=0; i<g->nbl; i++){
		for(int j=0; j<g->nbc; j++){

			if(est_vivante(i, j, *g)){
				g->cellules[i][j]++;
			}
			else g->cellules[i][j]=0;
		}
	}
}



void define_cyclique_non_cyclique(){
	// compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;
}

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	calcul_vieillissement(g);
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; j++)
		{
			v = compte_voisins_vivants_en_mode_cyclique(i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else if ( v==3 )
			{ // evolution d'une cellule morte
				set_vivante(i,j,*g);
			}
			else set_morte(i, j, *g);
		}
	}
	return;
}
