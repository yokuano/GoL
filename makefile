main: ./src/main.o ./src/grille.o ./src/io.o ./src/jeu.o
	gcc -o main ./src/main.o ./src/grille.o ./src/io.o ./src/jeu.o -lm

grille.o: ./src/grille.c grille.h
	gcc -o ./src/grille.o -c grille.c -Wall

io.o: ./src/io.c ./src/io.h ./src/grille.h ./src/jeu.h
	gcc -o ./src/io.o -c ./src/io.c -Wall

jeu.o: ./src/jeu.c ./src/jeu.h ./src/grille.h
	gcc -o ./src/jeu.o -c ./src/jeu.c -Wall

main.o: ./src/main.c ./src/grille.h ./src/jeu.h ./src/io.h
	gcc -o ./src/main.o -c ./src/main.c -Wall 

clean:
	rm -rf ./src/*.o main *.tar.xz

dist:
	tar -cJvf BendrissMohamedDris-GoL-version.tar.xz src makefile Doxyfile