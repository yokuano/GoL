/**
 * \file grille.c
 * \brief Ensemles de fonctions qui permettent de **manipuller des grilles**
 * \author Bendriss Mohamed Dris
 * 
 * @copyright Copyright (c) 2021
 */

#include "grille.h"

void alloue_grille(int l, int c, grille* g){

	g->nbc=c;
	g->nbl=l;
	g->cellules=calloc(l, sizeof(int*));
	for(int i=0; i<l; i++){
		g->cellules[i]= calloc(c, sizeof(int));	
	}

}


void libere_grille (grille* g){
	
	for(int i=0; i<g->nbl; i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
	return;

}

void init_grille_from_file (char * filename, grille* g){

	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, non_viable=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & non_viable);
	for (n=0; n< non_viable; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_nonviable(i,j,*g);
	}
	
	fclose (pfile);
	return;

}


void copie_grille (grille gs, grille gd){

	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
	
}

bool testEquivalenceGrille(grille* g1, grille* g2){
    for(int i=0; i<g1->nbl; i++){
        for(int j=0; j<g1->nbc; j++){
            if(g1->cellules[i][j]!=g2->cellules[i][j]) return false;
        }
    }
    return true;
}

bool testVideGrille(grille* g){
    for(int i=0; i<g->nbl; i++){
        for(int j=0; j<g->nbc; j++){
            if(est_vivante(i, j, *g)) return false;
        }
    }
    return true;
}
