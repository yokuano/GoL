#include <stdio.h>
#include <stdlib.h>
#include "displaycairo.h"

int temps=0;
char *tempsEvolution;

void print_lignes(cairo_surface_t *surface, cairo_t *cr, grille* g, int debut_ligne_x, int debut_ligne_y){

    cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
    cairo_move_to(cr, debut_ligne_x, debut_ligne_y);

    for(int i=0; i<=g->nbl; i++){
        cairo_line_to(cr, debut_ligne_x+SQUARE_SIZE*g->nbc, debut_ligne_y);
        cairo_set_line_width (cr, 1);
        debut_ligne_y+=SQUARE_SIZE;
        cairo_move_to(cr, debut_ligne_x, debut_ligne_y);
    }

    cairo_stroke(cr);
    

}

void print_colonnes(cairo_surface_t *surface, cairo_t *cr, grille* g, int debut_colonne_x, int debut_colonne_y){

    cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
    cairo_move_to(cr, debut_colonne_x, debut_colonne_y);

    for(int i=0; i<=g->nbc; i++){
        cairo_line_to(cr, debut_colonne_x, debut_colonne_y+SQUARE_SIZE*g->nbl);
        cairo_set_line_width (cr, 1);
        debut_colonne_x+=SQUARE_SIZE;
        cairo_move_to(cr, debut_colonne_x, debut_colonne_y);
    }
    cairo_stroke(cr);

}


void print_grille(cairo_surface_t *surface, grille *g){

    cairo_t *cr;
	cr=cairo_create(surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);

    for(int i=0; i<g->nbl; i++){
        for(int j=0; j<g->nbc; j++){
            if(est_vivante(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+100, i*SQUARE_SIZE+100, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 0.0, 1.0-0.1*g->cellules[i][j], 0.0);
	            cairo_fill(cr);
            }
            else if(!est_viable(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+100, i*SQUARE_SIZE+100, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	            cairo_fill(cr);
            }
            else{
                cairo_rectangle(cr,j*SQUARE_SIZE+100, i*SQUARE_SIZE+100, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	            cairo_fill(cr);
            }
        }
        print_colonnes(surface, cr, g, 100, 100);
        print_lignes(surface, cr, g, 100, 100);
    }

}
