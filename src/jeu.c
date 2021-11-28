/**
 * \file jeu.c
 * \brief Ensembles de fonctions permettant de **faire avancer le cours du jeu**
 * \author Bendriss Mohamed Dris
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "jeu.h"

int vieillsement=0;
int timeEvo=0;
int generationOscillante=1;

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

int v=0, l=g.nbl, c=g.nbc;

	if(i>0 && j>0)
		v+=est_vivante((i-1),(j-1),g);
	if(i>0)
		v+=est_vivante((i-1),j,g);
	if(j>0)
		v+=est_vivante(i,(j-1),g);
	if(i<(l-1))
		v+=est_vivante((i+1),j,g);
	if(j<(c-1))
		v+=est_vivante(i,(j+1),g);
	if (i>0 && j<(c-1))
		v+=est_vivante((i-1),(j+1),g);
	if(i<(l-1) && j>0)
		v+=est_vivante((i+1),(j-1),g);
	if(i<(l-1) && j<(c-1))
		v+=est_vivante((i+1),(j+1),g);
	return v;

}


int (*compte_voisins_vivants) (int, int, grille)=compte_voisins_vivants_en_mode_cyclique;


void calcul_vieillissement(grille *g){

	for(int i=0; i<g->nbl; i++){
		for(int j=0; j<g->nbc; j++){

			if(est_viable(i, j, *g)){
				if(est_vivante(i, j, *g) && vieillsement==1){
					g->cellules[i][j]++;
				}
				if(g->cellules[i][j]>9) set_morte(i, j, *g);
			}
		}
	}

}

int calcul_oscillation(grille *g){
	int limit=512;
	int oscillation=0;
	grille g2;
	grille g3;
	alloue_grille(g->nbl, g->nbc, &g2);
	alloue_grille(g->nbl, g->nbc, &g3);
	copie_grille(*g, g2);
	do{
		if(testVideGrille(&g2)){
			generationOscillante=oscillation+1;
			oscillation=0;
			break;
		}
		evolue(&g2, &g3);
		oscillation++;
	}while(!(testEquivalenceGrille(g, &g2)) && oscillation<limit);
	if(oscillation==limit) oscillation=-1;
	libere_grille(&g2);
	libere_grille(&g3);
	return oscillation;
}

int calcul_oscillation_wrapper(grille *g, grille *gc){
	grille g1;
	alloue_grille(g->nbl, g->nbc, &g1);
	copie_grille(*g, g1);

	if(calcul_oscillation(&g1)>-1 && calcul_oscillation(&g1)!=512) {
		return calcul_oscillation(&g1);
	}
	else if(generationOscillante!=512){
		evolue(&g1, gc);
		generationOscillante++;
		return calcul_oscillation_wrapper(&g1, gc);
	}
	return -1;									// Aucune oscillation trouvé au bout des 512 générations testées (cas extremement rare mais à prendre en compte)
}


void evolue (grille *g, grille *gc){

	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	calcul_vieillissement(g);
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; j++)
		{
			if(est_viable(i, j, *gc)){
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
	}
	return;
}
