main: main.o grille.o io.o jeu.o
	gcc -o main main.o grille.o io.o jeu.o -lm

grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c -Wall

io.o: io.c io.h grille.h jeu.h
	gcc -o io.o -c io.c -Wall

jeu.o: jeu.c jeu.h grille.h
	gcc -o jeu.o -c jeu.c -Wall

main.o: main.c grille.h jeu.h io.h
	gcc -o main.o -c main.c -Wall 

clean:
	rm -rf *.o main

dist:
	tar -cJvf CodeBendrissMohamedDris.tar.xz *.c *.h makefile