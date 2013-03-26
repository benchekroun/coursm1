# Tentative de Makefile générique pour les applications OpenGL
# modèle le stage sur les ventricules.

# le compilateur
CXX = g++ 

# les sources

SRC = tutoriel5 lecteur
EXE = tutoriel5
# Les options de compilations : essentiellement les librairies.
#LIBS = -lGL -lGLU -lglut -lm
LIBS = -lGL -lglut -lm -lGLU -lz -lpng12
LIBSDIR = -L/usr/X11R6/lib
INCLDIR = -I/usr/include/GL -I/usr/include/libpng12 

# La compilation
SOURCEFILES = $(SRC:=.cpp)
OBJECTFILES = $(SRC:=.o)

$(EXE): $(OBJECTFILES)
	@echo "         ===== linking ====="
	$(CXX) $(LIBSDIR) -o $(EXE) $(OBJECTFILES) $(LIBS)

.cpp.o:
	@echo "          -----" $@ "-----"
	$(CXX) $(INCLDIR) -c -o $@ $<



# Pour le nettoyage complet d'une compilation.
clean:
	rm -f *~ *.o core

