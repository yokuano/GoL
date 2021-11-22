.PHONY: clean doc dist all

CFLAGS+= -Wall -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
OPATH = obj/
BPATH = bin/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj bin dist doc lib

vpath %.c src/
vpath %.h include/

ifeq (TEXTE,$(MODE))

main : libjeu.a
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ lib/$^ -lm -ljeu -L lib
	mv *.o $(OPATH)
	mv main $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) -Iinclude $(CFLAGS) -c -o $@ $<

libjeu.a: main.o grille.o io.o jeu.o
	ar rvs libjeu.a $^ 
	mkdir -p lib
	ranlib libjeu.a
	mv libjeu.a lib/

else

cairomain : libjeu.a
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ lib/$^ -lm -ljeu -L lib $(LDFLAGS)
	mv *.o $(OPATH)
	mv cairomain $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

libjeu.a: cairomain.o displaycairo.o io.o grille.o jeu.o
	ar rvs libjeu.a $^ 
	mkdir -p lib
	ranlib libjeu.a
	mv libjeu.a lib/

endif

doc:
	$(DOC)

clean:
	rm -rf $(DEL)

dist:
	mkdir -p dist
	tar -cJvf BendrissMohamedDris-GoL-v4.2.0.tar.xz $(ZIP)
	mv *.xz dist
