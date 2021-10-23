.PHONY: clean doc dist all

CFLAGS+= -Wall
CPPFLAGS += -I include
OPATH = obj/
DOCGEN= doxygen
ARCHIVE= src makefile Doxyfile grilles README.md
BIN= obj/ main *.tar.xz doc/


vpath %.c src/

all: main

main : $(addprefix $(OPATH), main.o grille.o io.o jeu.o)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OPATH):
	mkdir $@

$(OPATH)%.o : %.c | $(OPATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


doc:
	$(DOCGEN)

clean:
	rm -rf $(BIN)

dist:
	tar -cJvf BendrissMohamedDris-GoL-version.tar.xz $(ARCHIVE)