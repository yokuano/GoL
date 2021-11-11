#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"
#include "displaycairo.h"

#define SIZEX 1000
#define SIZEY 1000

extern int vieillsement;

int main (int argc, char *argv[]){
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

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
			print_grille(cs, &g);
		} 
		else if(e.type==ButtonPress && e.xbutton.button == Button1){ // evolution
			evolue(&g,&gc);
			print_grille(cs, &g);
		}
		else if(e.type==ButtonPress && e.xbutton.button == Button3){ //quitter 
			break;
		}
		else if(e.type==KeyPress && e.xkey.keycode == 55){ // vileillsement
			if(vieillsement==0) vieillsement=1;
			else vieillsement=0;
		}
		else if(e.type==KeyPress && e.xkey.keycode == 54){ // cyclique
			if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
			else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;
		}
		
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}