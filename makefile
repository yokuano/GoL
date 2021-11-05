.PHONY: clean doc dist all

CFLAGS+= -Wall -g
CPPFLAGS+= -I include
OPATH = obj/
BPATH = bin/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj bin dist doc

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
	mkdir -p dist
	tar -cJvf BendrissMohamedDris-GoL-v3.0.1.tar.xz $(ZIP)
	mv *.xz dist
