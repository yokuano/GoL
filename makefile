.PHONY: clean doc dist all
EXEC  = main
OPATH = obj/
BPATH = bin/
LPATH = lib/
LIB   = jeu.o grille.o
ZIP   = src makefile Doxyfile grilles README.md include
DOC   = doxygen
DEL   = obj bin dist doc lib
CFLAGS += -Wall -g
CPPFLAGS += -Iinclude
LDFLAGS = -lm -ljeu -L lib

vpath %.c src/
vpath %.h include/

ifeq (TEXTE,$(MODE))
	LIB+=io.o main.o

else
	LDFLAGS += -lcairo -lm -lX11
	CPPFLAGS += -I/usr/include/cairo
	LIB += displaycairo.o cairomain.o

endif

$(EXEC) : libjeu.a
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ lib/$^ $(LDFLAGS)
	mv *.o $(OPATH)
	mv $(EXEC) $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

libjeu.a: $(LIB)
	ar rvs libjeu.a $(LIB)
	mkdir -p $(LPATH) $(BPATH) $(OPATH)
	ranlib libjeu.a
	mv libjeu.a lib/

doc:
	$(DOC)

clean:
	rm -rf $(DEL)

dist:
	mkdir -p dist
	tar -cJvf BendrissMohamedDris-GoL-v4.2.0.tar.xz $(ZIP)
	mv *.xz dist