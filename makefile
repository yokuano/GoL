.PHONY: clean doc dist all

CFLAGS+= -Wall -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
OPATH = obj/
BPATH = bin/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj bin dist doc

vpath %.c src/
vpath %.h include/

ifeq (TEXTE,$(MODE))

main : main.o grille.o io.o jeu.o
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	mv *.o $(OPATH)
	mv main $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) -Iinclude $(CFLAGS) -c -o $@ $<

else

cairomain : cairomain.o displaycairo.o grille.o io.o jeu.o
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	mv *.o $(OPATH)
	mv cairomain $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

endif

doc:
	$(DOC)

clean:
	rm -rf $(DEL)

dist:
	mkdir -p dist
	tar -cJvf BendrissMohamedDris-GoL-v4.1.1.tar.xz $(ZIP)
	mv *.xz dist
