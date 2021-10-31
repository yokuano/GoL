.PHONY: clean docs dist all

CFLAGS+= -Wall -g
CPPFLAGS+= -I include
OPATH = obj/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj/ main *.tar.xz doc/


vpath %.c src/
vpath %.h include/

all: main

main : main.o grille.o io.o jeu.o
	mkdir -p $(OPATH)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	mv *.o $(OPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

docs:
	$(DOC)

clean:
	rm -rf $(DEL)

dist:
	tar -cJvf BendrissMohamedDris-GoL-v2.9.2.tar.xz $(ZIP)
