.PHONY: clean doc dist all

CFLAGS+= -Wall -g
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
OPATH = obj/
BPATH = bin/
LPATH= lib/
DOC= doxygen
ZIP= src makefile Doxyfile grilles README.md include
DEL= obj bin dist doc lib
LIB=jeu.o grille.o
MODE=GRAPH

vpath %.c src/
vpath %.h include/

ifeq (TEXTE,$(MODE))

main : libjeu.a
	$(CC) $(CFLAGS) -o $@ lib/$^ -lm -ljeu -L lib
	mv *.o $(OPATH)
	mv main $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) -Iinclude $(CFLAGS) -c -o $@ $<

else

cairomain : libjeu.a
	$(CC) $(CFLAGS) -o $@ lib/$^ -lm -ljeu -L lib $(LDFLAGS)
	mv *.o $(OPATH)
	mv cairomain $(BPATH)

$(OPATH)%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

endif

libjeu.a: io.o main.o cairomain.o displaycairo.o $(LIB)
	@if [ $(MODE) = "TEXTE" ] ; \
		then \
			ar rvs libjeu.a $(LIB) io.o main.o; \
	else ar rvs libjeu.a $(LIB) cairomain.o displaycairo.o; \
	fi
	mkdir -p $(LPATH)
	mkdir -p $(OPATH)
	mkdir -p $(BPATH)
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