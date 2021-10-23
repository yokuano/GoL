OPATH = obj/
DOCGEN= doxygen
CFLAGS+= -Wall
ARCHIVE+= src makefile Doxyfile grilles README
LDFLAGS= -lm
BIN+= obj main *.tar.xz doc


vpath %.c src/

main : $(addprefix $(OPATH), main.o grille.o io.o jeu.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OPATH):
	mkdir $@

$(OPATH)%.o : %.c | $(OPATH)
	$(CC) $(CFLAGS) -c $< -o $@


doc:
	$(DOCGEN)

clean:
	rm -rf $(BIN)

dist:
	tar -cJvf BendrissMohamedDris-GoL-version.tar.xz $(ARCHIVE)