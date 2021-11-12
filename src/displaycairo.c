#include <stdio.h>
#include <stdlib.h>
#include "displaycairo.h"

int temps=0;
char *tempsEvolution;
extern int vieillsement;

int getX_SizeWindow(){
    int xSize;
    FILE* pp;
    pp=popen("xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1", "r");
    if(pp==NULL){
        printf("Couldn't load Window size");
        exit(1);
    }
    char* tmp;
    char buf[5];
    tmp=fgets(buf, sizeof buf, pp);
    xSize=atoi(tmp);
    pclose(pp);
    return xSize;

}

int getY_SizeWindow(){
    int ySize;
    FILE* pp;
    pp=popen("xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2", "r");
    if(pp==NULL){
        printf("Couldn't load Window size");
        exit(1);
    }
    char* tmp;
    char buf[5];
    tmp=fgets(buf, sizeof buf, pp);
    ySize=atoi(tmp);
    pclose(pp);
    return ySize;
}

void printRectangle(cairo_t *cr, int debutx, int debuty, int x, int y, int bold){
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, debutx, debuty);
    cairo_line_to(cr, debutx+x, debuty);
    cairo_move_to(cr, debutx+x, debuty);
    cairo_line_to(cr, debutx+x, debuty+y);
    cairo_move_to(cr, debutx+x, debuty+y);
    cairo_line_to(cr, debutx, debuty+y);
    cairo_move_to(cr, debutx, debuty+y);
    cairo_line_to(cr, debutx, debuty);
    cairo_set_line_width(cr, bold);
    cairo_stroke(cr);
}


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

void print_GUI_vileillssement(int vieillsement, cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);
    
    cairo_rectangle(cr, 0, 0, sizeX/3, 100);
    vieillsement==0 ? cairo_set_source_rgb(cr, 0.94901, 0.38742, 0.41531) : cairo_set_source_rgb(cr, 0.69019, 0.94901, 0.71372);
    cairo_fill(cr);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_select_font_face(cr, "Purisa",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
    cairo_move_to(cr, 30, 30);
    cairo_show_text(cr, "vieillsement");


    cairo_destroy(cr); // destroy cairo mask
}

void print_GUI_cycle(int (*compte_voisins_vivants) (int, int, grille), cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);

    cairo_rectangle(cr, 2*sizeX/3, 0, sizeX/3, 100);
    compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique ? cairo_set_source_rgb(cr, 0.94901, 0.38742, 0.41531) : cairo_set_source_rgb(cr, 0.69019, 0.94901, 0.71372);
    cairo_fill(cr);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_select_font_face(cr, "Purisa",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
    cairo_move_to(cr, sizeX-150, 30);
    cairo_show_text(cr, "cyclique");
    

    cairo_destroy(cr); // destroy cairo mask
}

void print_GUI_grille(cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
    cr=cairo_create(surface);

    cairo_rectangle(cr, sizeX/3, 2*sizeX/3, sizeX/3, 100);
    cairo_set_source_rgb(cr, 0.38, 0.38, 0.38);
    cairo_fill(cr);

    cairo_destroy(cr);

}

void print_grille(cairo_surface_t *surface, grille *g){

    cairo_t *cr;
	cr=cairo_create(surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint(cr);

    int debutTabX=(getX_SizeWindow()-SQUARE_SIZE*(g->nbc+1))/2;
    int debutTabY=(getY_SizeWindow()-SQUARE_SIZE*(g->nbl+1))/2;

    for(int i=0; i<g->nbl; i++){
        for(int j=0; j<g->nbc; j++){
            if(est_vivante(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 0.0, 1.0-0.1*g->cellules[i][j], 0.0);
	            cairo_fill(cr);
            }
            else if(!est_viable(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	            cairo_fill(cr);
            }
            else{
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	            cairo_fill(cr);
            }
        }
    }
    print_colonnes(surface, cr, g, debutTabX, debutTabY);
    print_lignes(surface, cr, g, debutTabX, debutTabY);
    print_GUI_vileillssement(vieillsement, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_cycle(compte_voisins_vivants, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_grille(surface, getX_SizeWindow(), getY_SizeWindow());

    printRectangle(cr, 0, 0, getX_SizeWindow()/3, 100, 3);
    printRectangle(cr, getX_SizeWindow(), 0, 2*getX_SizeWindow()/3, 100, 3);
    printRectangle(cr, 2*getX_SizeWindow()/3, 0, getX_SizeWindow()/3, 100, 3);


    cairo_destroy(cr); // destroy cairo mask
}


