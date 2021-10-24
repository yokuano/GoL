/**
 * \file grille.c
 * \brief Ensemles de fonctions qui permettent de **manipuller des grilles**\n
 * 		  A l'aide de ce code, on peut: creer une grille, la suprimmer, créer une grille à partir d'un fichier, copier une grille
 * \author Bendriss Mohamed Dris **uniquement pour les fonctions allouer_grille et libere grille**
 */
#include "grille.h"

/**
 * \param[in] l 
 * \param[in] c
 * \param[out] g
 * \brief Alloue une **grille** de taille **l*c**, et initialise **toutes les cellules à mortes**
 */
void alloue_grille(int l, int c, grille* g){

	g->nbc=c;
	g->nbl=l;
	g->cellules= malloc(sizeof(int*)*l);
	for(int i=0; i<l; i++){
		g->cellules[i]= calloc(c, sizeof(int));	
	}
}

/**
 * \brief **Libère** la grille mise en paramètre de l'espace mémoire
 * \param[out] g
 */
void libere_grille (grille* g){
	
	for(int i=0; i<g->nbl; i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
	return;
}

/**
 * \param[in] filename
 * \param[out] g
 * \brief **Créer** une grille **à partir d'un fichier** mis en argument filename
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 * \param[in] gs
 * \param[out] gd
 * \brief **Copie** la grille **gs** dans la grille **gd**
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
