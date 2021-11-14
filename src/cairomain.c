/**
 * @file cairomain.c
 * @author Bendriss Mohamed Dris
 * @brief Fichier main qui permet de lancer le jeux en mode graphique 
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "displaycairo.h"

extern int vieillsement;
extern int timeEvo;
extern int darkmode; 


int main (int argc, char *argv[]){
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	int SIZEX=getX_SizeWindow();
	int SIZEY=getY_SizeWindow();

    grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Game of Life by Bendriss Mohamed Dris");
	XSelectInput(dpy, win, KeyPressMask|ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			print_GraphicUserInterface(cs, &g);
		} 
		else if(e.type==ButtonPress && e.xbutton.button == Button1){ // evolution
			evolue(&g,&gc);
			timeEvo++;
			print_GraphicUserInterface(cs, &g);
		}
		else if(e.type==ButtonPress && e.xbutton.button == Button3){ //quitter 
			break;
		}
		else if(e.type==KeyPress && e.xkey.keycode == 55){ // vileillsement
			if(vieillsement==0) vieillsement=1;
			else vieillsement=0;
			print_GraphicUserInterface(cs, &g);
		}
		else if(e.type==KeyPress && e.xkey.keycode == 54){ // cyclique
			if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
			else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;
			print_GraphicUserInterface(cs, &g);
		}
		else if(e.type==KeyPress && e.xkey.keycode == 57){
			XNextEvent(dpy, &e);
				if(e.type==KeyPress && e.xkey.keycode>=10 && e.xkey.keycode<19){
					efface_grille(g);
					libere_grille(&g);
					libere_grille(&gc);
					init_grille_from_file(newGrille(e.xkey.keycode), &g);
					alloue_grille(g.nbl, g.nbc, &gc);
					timeEvo=0;
					print_GraphicUserInterface(cs, &g);
				}
			}
		else if(e.type==KeyPress && e.xkey.keycode == 40){
			darkmode=darkmode==1? 0:1;
			print_GraphicUserInterface(cs, &g);
		}
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	system("clear");
	printf("X11 Display has been closed due to user using right click on their mouse\n");
	return 0;
		
}