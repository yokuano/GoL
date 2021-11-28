/**
 * \file displaycairo.c
 * \brief Ensemble de fonction qui permet **d'afficher et d'actualiser la fenêtre graphique**
 * \author Bendriss Mohamed Dris
 * 
 * \copyright Copyright (c) 2021
 * 
 */

#include "displaycairo.h"

extern int timeEvo;
extern int vieillsement;
extern int generationOscillante;

/**
 * @brief 
 * 
 */
int darkmode=1;

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* newGrille(int event){
    char n=event-9+48;
    char tmp[2]={n, '\0'};
    char* newGrille;
    char* filextention=concat(tmp, ".txt");
    newGrille=concat("./grilles/grille", filextention);         
    free(filextention);                        
    return newGrille;
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


void print_lignes(cairo_t *cr, grille* g, int debut_ligne_x, int debut_ligne_y, int squaresize){

    SET_SOURCE_BLACK(cr);
    cairo_move_to(cr, debut_ligne_x, debut_ligne_y);

    for(int i=0; i<=g->nbl; i++){

        cairo_line_to(cr, debut_ligne_x+squaresize*g->nbc, debut_ligne_y);
        cairo_set_line_width (cr, 2);
        debut_ligne_y+=squaresize;
        cairo_move_to(cr, debut_ligne_x, debut_ligne_y);

    }

    cairo_stroke(cr);

}

void print_colonnes(cairo_t *cr, grille* g, int debut_colonne_x, int debut_colonne_y, int squaresize){

    SET_SOURCE_BLACK(cr);
    cairo_move_to(cr, debut_colonne_x, debut_colonne_y);

    for(int i=0; i<=g->nbc; i++){

        cairo_line_to(cr, debut_colonne_x, debut_colonne_y+squaresize*g->nbl);
        cairo_set_line_width (cr, 2);
        debut_colonne_x+=squaresize;
        cairo_move_to(cr, debut_colonne_x, debut_colonne_y);

    }

    cairo_stroke(cr);

}

void print_GUI_vieillsement(int vieillsement, cairo_surface_t *surface, int sizeX, int sizeY){

    cairo_t *cr;
	cr=cairo_create(surface);
    char* aging="Vieillissement";
    double x, y;
    cairo_text_extents_t extents;
    
    cairo_rectangle(cr, 0, 0, sizeX/3, GUI_Y);
    vieillsement==0 ? SET_SOURCE_RED(cr) : SET_SOURCE_GREEN(cr);
    cairo_fill(cr);

    cairo_text_extents(cr, aging, &extents); // Get position to start writing 
    x=sizeX/6-extents.width;
    y=GUI_Y/2;

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

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
    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);    
    cairo_move_to(cr, getX_SizeWindow()/3, GUI_Y/2);
    cairo_set_font_size(cr, 20);

    char evo[12];
    snprintf(evo, 12, "%d", timeEvo);
    char* evo2=concat("Temps d'évolution: ", evo);

    cairo_text_extents(cr, evo2, &extents); // Get position to start writing 
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
    char* cycle="Cyclique";
    double x, y;
    cairo_text_extents_t extents;

    cairo_rectangle(cr, 2*sizeX/3, 0, sizeX/3, GUI_Y);

    compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique ? 
    SET_SOURCE_GREEN(cr) : SET_SOURCE_RED(cr);

    cairo_fill(cr);

    cairo_text_extents(cr, cycle, &extents); // Get position to start writing 
    x=sizeX-2*extents.width-sizeX/6;
    y=GUI_Y/2;

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, cycle);
    
    printRectangle(cr, 2*getX_SizeWindow()/3, 0, getX_SizeWindow()/3, GUI_Y, 3);

    cairo_destroy(cr); // destroy cairo mask
}


void print_grille(cairo_surface_t *surface, grille *g, int debutTabX, int debutTabY, int squaresize){

    cairo_t *cr;
	cr=cairo_create(surface);

    for(int i=0; i<g->nbl; i++){
        for(int j=0; j<g->nbc; j++){
            if(est_vivante(i, j, *g)){
                cairo_rectangle(cr,j*squaresize+debutTabX, i*squaresize+debutTabY, squaresize, squaresize);
	            cairo_set_source_rgba (cr, 0.0, 1, 0.0, 1.0-0.1*g->cellules[i][j]);
	            cairo_fill(cr);
            }
            else if(!est_viable(i, j, *g)){
                cairo_rectangle(cr,j*squaresize+debutTabX, i*squaresize+debutTabY, squaresize, squaresize);
	            cairo_set_source_rgba (cr, 1, 0, 0, 2);
	            cairo_fill(cr);
            }
            else{
                cairo_rectangle(cr,j*squaresize+debutTabX, i*squaresize+debutTabY, squaresize, squaresize);
	            set_bg(cr);
	            cairo_fill(cr);
            }
        }
    }

    cairo_destroy(cr); // destroy cairo mask
}


void print_crtl(cairo_surface_t *surface){
    
    cairo_t *cr;
	cr=cairo_create(surface);

    cairo_rectangle(cr, 0, GUI_Y, getX_SizeWindow()/3, getY_SizeWindow()-100); 
    cairo_set_source_rgb(cr, 0.38, 0.38, 0.38);
    cairo_fill(cr);
    printRectangle(cr, 0, GUI_Y, getX_SizeWindow()/3, getY_SizeWindow()-100, 3);

    
    cairo_select_font_face(cr, "Miriam Mono", 0, 0.5);
    cairo_set_font_size(cr, 15);

    cairo_move_to(cr, 25, 150);
    cairo_show_text(cr, "Commandes Souris");
    cairo_move_to(cr, 25, 180);
    cairo_show_text(cr, "Left Click : Evolution de la grille");
    cairo_move_to(cr, 25, 200);
    cairo_show_text(cr, "Right Click: Quitter le jeu");

    cairo_move_to(cr, 25, 240);
    cairo_show_text(cr, "Commandes Clavier");
    cairo_move_to(cr, 25, 270);
    cairo_show_text(cr, "V : Activer/Desactiver le vieillsement");
    cairo_move_to(cr, 25, 290);
    cairo_show_text(cr, "C : Voisinage Cyclique/Non cyclique");
    cairo_move_to(cr, 25, 310);
    cairo_show_text(cr, "N : Charger une nouvelle grille");
    cairo_move_to(cr, 25, 330);
    cairo_show_text(cr, "O : Lancer le test d'oscillation");

    cairo_move_to(cr, 25, 370);
    cairo_show_text(cr, "Code couleur");
    SET_SOURCE_GREEN(cr);
    cairo_rectangle(cr, 25, 387, 20, 15);
    cairo_fill(cr);
    cairo_move_to(cr, 47, 400);
    SET_SOURCE_BLACK(cr);
    cairo_show_text(cr, " : Fonctionalité activé");
    SET_SOURCE_RED(cr);
    cairo_rectangle(cr, 25, 407, 20, 15);
    cairo_fill(cr);
    cairo_move_to(cr, 47, 420);
    SET_SOURCE_BLACK(cr);
    cairo_show_text(cr, " : Fonctionalité désactivé");
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, 25, 427, 20, 15);
    cairo_fill(cr);
    cairo_move_to(cr, 47, 440);
    SET_SOURCE_BLACK(cr);
    cairo_show_text(cr, " : Cellule vivante");
    set_bg(cr);
    cairo_rectangle(cr, 25, 447, 20, 15);
    cairo_fill(cr);
    cairo_move_to(cr, 47, 460);
    SET_SOURCE_BLACK(cr);
    cairo_show_text(cr, " : Cellule morte");
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, 25, 467, 20, 15);
    cairo_fill(cr);
    cairo_move_to(cr, 47, 480);
    SET_SOURCE_BLACK(cr);
    cairo_show_text(cr, " : Cellule non viable");

    cairo_destroy(cr); // destroy cairo mask

}

void print_oscillation(cairo_surface_t* surface, grille* g, grille* gc){

    cairo_t *cr;
	cr=cairo_create(surface);
    grille demo, demo2;
	alloue_grille(g->nbl, g->nbc, &demo);
    alloue_grille(g->nbl, g->nbc, &demo2);
    copie_grille(*g, demo);

    int debutX=2*getX_SizeWindow()/3;

    cairo_rectangle(cr, debutX, GUI_Y, getX_SizeWindow()/3, getY_SizeWindow()-GUI_Y); 
    cairo_set_source_rgb(cr, 0.38, 0.38, 0.38);
    cairo_fill(cr);
    printRectangle(cr, debutX, GUI_Y, getX_SizeWindow()/3, getY_SizeWindow()-GUI_Y, 3);
    
    char osc[12];
    snprintf(osc, 12, "%d", calcul_oscillation_wrapper(g, gc));
    char* finalosc=concat("Periode d'oscillation: ", osc);

    for(int i=1; i!=generationOscillante; i++){
        evolue(&demo, &demo2);
    }

    print_grille(surface, &demo, 5*getX_SizeWindow()/6, GUI_Y+70, 10);
    print_colonnes(cr, &demo, 5*getX_SizeWindow()/6 , GUI_Y+70, 10);
    print_lignes(cr, &demo, 5*getX_SizeWindow()/6, GUI_Y+70, 10);

    SET_SOURCE_BLACK(cr);
    cairo_select_font_face(cr, "Miriam Mono", 0, 0.5);
    cairo_set_font_size(cr, 15);

    cairo_move_to(cr, debutX + 17, GUI_Y+20);
    cairo_show_text(cr, "Etat de la grille lors de la première apparition du motif oscillant"); 

    cairo_move_to(cr, debutX + 17, GUI_Y+80);
    cairo_show_text(cr, "Vieillsement: "); 
    cairo_move_to(cr, debutX + 17, GUI_Y+105);
    cairo_show_text(cr, "Voisinage cyclique: ");
    cairo_move_to(cr, debutX + 17, GUI_Y+130);
    char tmp[12];
    snprintf(tmp, 12, "%d", generationOscillante-1);
    char* finaltmp=concat("Temps d'évolution:  ", tmp);
    cairo_show_text(cr, finaltmp);
    cairo_move_to(cr, debutX + 17, GUI_Y+155);
    cairo_show_text(cr, finalosc);

    SET_SOURCE_GREEN(cr);
    vieillsement ? SET_SOURCE_GREEN(cr) : SET_SOURCE_RED(cr);
    cairo_rectangle(cr, debutX+170, GUI_Y+68, 20, 15);
    cairo_fill(cr);
    compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique ? SET_SOURCE_GREEN(cr) : SET_SOURCE_RED(cr);
    cairo_rectangle(cr, debutX+170, GUI_Y+93, 20, 15);
    cairo_fill(cr);

    libere_grille(&demo);
    libere_grille(&demo2);
    free(finaltmp);
    free(finalosc);

    cairo_destroy(cr); // destroy cairo mask
}

void print_GraphicUserInterface(cairo_surface_t *surface, grille *g){

    cairo_t *cr;
	cr=cairo_create(surface);

    set_bg(cr);
    cairo_paint(cr);

    int debutTabX=(getX_SizeWindow()-SQUARE_SIZE*(g->nbc+1))/2;
    int debutTabY=(getY_SizeWindow()-SQUARE_SIZE*(g->nbl+1))/2;

    print_grille(surface, g, debutTabX, debutTabY, SQUARE_SIZE);

    print_colonnes(cr, g, debutTabX, debutTabY, SQUARE_SIZE);
    print_lignes(cr, g, debutTabX, debutTabY, SQUARE_SIZE);

    print_GUI_vieillsement(vieillsement, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_cycle(compte_voisins_vivants, surface, getX_SizeWindow(), getY_SizeWindow());
    print_GUI_grille(surface, getX_SizeWindow(), getY_SizeWindow());

    cairo_destroy(cr); // destroy cairo mask

}


void debut_jeu_cairo(grille *g, grille *gc){

    // X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	int SIZEX=getX_SizeWindow();
	int SIZEY=getY_SizeWindow();

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
			print_GraphicUserInterface(cs, g);
		} 
		else if(e.type==ButtonPress && e.xbutton.button == Button1){ // evolution
			evolue(g,gc);
			timeEvo++;
			print_GraphicUserInterface(cs, g);
		}
		else if(e.type==ButtonPress && e.xbutton.button == Button3){ //quitter 
			break;
		}
		else if(e.type==KeyPress && e.xkey.keycode == keycode("v")){ // vileillsement
			if(vieillsement==0) vieillsement=1;
			else vieillsement=0;
			print_GraphicUserInterface(cs, g);
		}
		else if(e.type==KeyPress && e.xkey.keycode == keycode("c")){ // cyclique
			if(compte_voisins_vivants==compte_voisins_vivants_en_mode_cyclique) compte_voisins_vivants=compte_voisins_vivants_en_mode_non_cyclique;
			else compte_voisins_vivants=compte_voisins_vivants_en_mode_cyclique;
			print_GraphicUserInterface(cs, g);
		}
		else if(e.type==KeyPress && e.xkey.keycode == keycode("n")){
			XNextEvent(dpy, &e);
				if(e.type==KeyPress && e.xkey.keycode>=keycode("1") && e.xkey.keycode<=keycode("9")){
					libere_grille(g);
					libere_grille(gc);
                    char* grillename=newGrille(e.xkey.keycode);
					init_grille_from_file(grillename, g);
					alloue_grille(g->nbl, g->nbc, gc);
					timeEvo=0;
					print_GraphicUserInterface(cs, g);
                    free(grillename);
				}
			}
		else if(e.type==KeyPress && e.xkey.keycode == keycode("d")){
			darkmode=darkmode==1? 0:1;
			print_GraphicUserInterface(cs, g);
		}

        else if(e.type==KeyPress && e.xkey.keycode == keycode("Control_L")){
            print_crtl(cs);
            XNextEvent(dpy, &e);
            while(e.xkey.keycode != keycode("q")) XNextEvent(dpy, &e);
            print_GraphicUserInterface(cs, g);
        }
        else if(e.type == KeyPress && e.xkey.keycode == keycode("o")){
            print_oscillation(cs, g, gc);
            XNextEvent(dpy, &e);
            while(e.xkey.keycode != keycode("q")) XNextEvent(dpy, &e);
            setGen();
            print_GraphicUserInterface(cs, g);
        }
	}

    cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	system("clear");
	printf("X11 Display has been closed due to user using right click on their mouse\n");

}