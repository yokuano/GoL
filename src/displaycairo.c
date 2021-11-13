/**
 * \file displaycairo.c
 * \brief Ensemble de fonction qui permet **d'afficher et d'actualiser la fenêtre graphique**
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "displaycairo.h"

extern int timeEvo;
extern int vieillsement;


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int getX_SizeWindow(){

    int xSize;                                  // Variable qui stoque la longueure X de l'ecran          
    FILE* pp;                                   // Ouverture Pipe
    pp=popen("xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1", "r");  // Lancement de la commande qui lit la longueure X de l'ecran
    if(pp==NULL){                               // Test au cas ou echec commande
        printf("Couldn't load Window size");
        exit(1);
    }
    char* tmp;                                  // Variable temportaire
    char buf[5];                                // buffer 
    tmp=fgets(buf, sizeof buf, pp);             // tmp prend en valeur le resultat de la commande lance dans la pipe
    xSize=atoi(tmp);                            // Conversion en entier de la chaine
    pclose(pp);                                 // Fermeture Pipe
    return xSize; 

}

int getY_SizeWindow(){

    int ySize;                                  // Variable qui stoque la longueure X de l'ecran          
    FILE* pp;                                   // Ouverture Pipe
    pp=popen("xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2", "r");  // Lancement de la commande qui lit la longueure X de l'ecran
    if(pp==NULL){                               // Test au cas ou echec commande
        printf("Couldn't load Window size");
        exit(1);
    }
    char* tmp;                                  // Variable temportaire
    char buf[5];                                // buffer 
    tmp=fgets(buf, sizeof buf, pp);             // tmp prend en valeur le resultat de la commande lance dans la pipe
    ySize=atoi(tmp);                            // Conversion en entier de la chaine
    pclose(pp);                                 // Fermeture Pipe
    return ySize; 
              
}

void printRectangle(cairo_t *cr, int debutx, int debuty, int x, int y, int bold){

    SET_SOURCE_BLACK(cr);
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


void print_lignes(cairo_t *cr, grille* g, int debut_ligne_x, int debut_ligne_y){

    SET_SOURCE_WHITE(cr);
    cairo_move_to(cr, debut_ligne_x, debut_ligne_y);

    for(int i=0; i<=g->nbl; i++){

        cairo_line_to(cr, debut_ligne_x+SQUARE_SIZE*g->nbc, debut_ligne_y);
        cairo_set_line_width (cr, 1);
        debut_ligne_y+=SQUARE_SIZE;
        cairo_move_to(cr, debut_ligne_x, debut_ligne_y);

    }

    cairo_stroke(cr);

}

void print_colonnes(cairo_t *cr, grille* g, int debut_colonne_x, int debut_colonne_y){

    SET_SOURCE_WHITE(cr);
    cairo_move_to(cr, debut_colonne_x, debut_colonne_y);

    for(int i=0; i<=g->nbc; i++){

        cairo_line_to(cr, debut_colonne_x, debut_colonne_y+SQUARE_SIZE*g->nbl);
        cairo_set_line_width (cr, 1);
        debut_colonne_x+=SQUARE_SIZE;
        cairo_move_to(cr, debut_colonne_x, debut_colonne_y);

    }

    cairo_stroke(cr);

}

void print_GUI_vieillsement(int vieillsement, cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);
    char* aging="vieillsement";
    double x, y;
    cairo_text_extents_t extents;
    
    cairo_rectangle(cr, 0, 0, sizeX/3, GUI_Y);
    vieillsement==0 ? SET_SOURCE_RED(cr) : SET_SOURCE_GREEN(cr);
    cairo_fill(cr);

    cairo_text_extents(cr, aging, &extents);
    x=sizeX/6-extents.width;
    y=GUI_Y/2;

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Purisa",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_BOLD);

        
    cairo_move_to(cr, x, y);
    cairo_set_font_size(cr, 20);
    cairo_show_text(cr, aging);

    printRectangle(cr, 0, 0, getX_SizeWindow()/3, GUI_Y, 3);

    cairo_destroy(cr); // destroy cairo mask
}

void print_GUI_grille(cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);
    double x, y;
    cairo_text_extents_t extents;

    cairo_rectangle(cr, sizeX/3+2, 0, sizeX/3-4, GUI_Y);
    cairo_set_source_rgb(cr, 0.38, 0.38, 0.38);
    cairo_fill(cr);

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Purisa",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_BOLD);

        
    cairo_move_to(cr, getX_SizeWindow()/3, GUI_Y/2);
    cairo_set_font_size(cr, 20);

    char evo[12];
    snprintf(evo, 12, "%d", timeEvo);
    char* evo2=concat("Temps d'évolution: ", evo);
    cairo_text_extents(cr, evo2, &extents);
    x=sizeX/2-extents.width/2;
    y=GUI_Y/2;

    cairo_move_to(cr, x, y);
    cairo_show_text(cr, evo2);
    free(evo2);

    printRectangle(cr, getX_SizeWindow()/3, 0, getX_SizeWindow()/3, GUI_Y, 3);

    cairo_destroy(cr); // destroy cairo mask
}

void print_GUI_cycle(int (*compte_voisins_vivants) (int, int, grille), cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);
    char* cycle="cyclique";
    double x, y;
    cairo_text_extents_t extents;

    cairo_rectangle(cr, 2*sizeX/3, 0, sizeX/3, GUI_Y);

    compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique ? 
    SET_SOURCE_RED(cr) : SET_SOURCE_GREEN(cr);

    cairo_fill(cr);

    cairo_text_extents(cr, cycle, &extents);
    x=sizeX-2*extents.width-sizeX/6;
    y=GUI_Y/2;

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Purisa",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, cycle);
    
    printRectangle(cr, 2*getX_SizeWindow()/3, 0, getX_SizeWindow()/3, GUI_Y, 3);

    cairo_destroy(cr); // destroy cairo mask
}


void print_grille(cairo_surface_t *surface, grille *g, int debutTabX, int debutTabY){

    cairo_t *cr;
	cr=cairo_create(surface);

    SET_SOURCE_GREY(cr);
	cairo_paint(cr);

    for(int i=0; i<g->nbl; i++){
        for(int j=0; j<g->nbc; j++){
            if(est_vivante(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgba (cr, 0.0, 1, 0.0, 1.0-0.1*g->cellules[i][j]);
	            cairo_fill(cr);
            }
            else if(!est_viable(i, j, *g)){
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            cairo_set_source_rgba (cr, 1, 0, 0, 2);
	            cairo_fill(cr);
            }
            else{
                cairo_rectangle(cr,j*SQUARE_SIZE+debutTabX, i*SQUARE_SIZE+debutTabY, SQUARE_SIZE, SQUARE_SIZE);
	            SET_SOURCE_GREY(cr);
	            cairo_fill(cr);
            }
        }
    }

    cairo_destroy(cr); // destroy cairo mask
}

void print_GraphicUserInterface(cairo_surface_t *surface, grille *g){

    cairo_t *cr;
	cr=cairo_create(surface);

    int debutTabX=(getX_SizeWindow()-SQUARE_SIZE*(g->nbc+1))/2;
    int debutTabY=(getY_SizeWindow()-SQUARE_SIZE*(g->nbl+1))/2;

    print_grille(surface, g, debutTabX, debutTabY);

    print_colonnes(cr, g, debutTabX, debutTabY);
    print_lignes(cr, g, debutTabX, debutTabY);

    print_GUI_vieillsement(vieillsement, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_cycle(compte_voisins_vivants, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_grille(surface, getX_SizeWindow(), getY_SizeWindow());

}


