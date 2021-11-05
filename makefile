.PHONY: clean doc dist all

CFLAGS+= -Wall -g
CPPFLAGS+= -I include
OPATH = obj/
BPATH = bin/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj/ bin/ *.tar.xz doc/

vpath %.c src/
vpath %.h include/

all: main

main : main.o grille.o io.o jeu.o
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	mv *.o $(OPATH)
	mv main $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

doc:
	$(DOC)

clean:
	rm -rf $(DEL)

dist:
	tar -cJvf BendrissMohamedDris-GoL-v2.8.0.tar.xz $(ZIP)
