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

int est_dans_grille(int i, int j, grille g){
	if(i>=0 && j>=0 && i<g.nbl && j<g.nbc){
		return 1;
	}
	return 0;
}


int compte_voisins_vivants_en_mode_non_cyclique(int i,int j,grille g){
int v=0, l=g.nbl, c=g.nbc;

	if(i>0 && j>0)
		v+=est_vivante((i-1),(j-1),g);
	if(i>0)
		v+=est_vivante((i-1),j,g);
	if (i>0 && j<(c-1))
		v+=est_vivante((i-1),(j+1),g);
	if(j>0)
		v+=est_vivante(i,(j-1),g);
	if(j<(c-1))
		v+=est_vivante(i,(j+1),g);
	if(i<(l-1) && j>0)
		v+=est_vivante((i+1),(j-1),g);
	if(i<(l-1))
		v+=est_vivante((i+1),j,g);
	if(i<(l-1) && j<(c-1))
		v+=est_vivante((i+1),(j+1),g);
	return v;
}


int (*compte_voisins_vivants) (int, int, grille)=compte_voisins_vivants_en_mode_cyclique;


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


void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	calcul_vieillissement(g);
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; j++)
		{
			v = (*compte_voisins_vivants)(i, j, *gc);
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
