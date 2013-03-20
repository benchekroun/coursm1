GXX=g++
CXXFLAGS = -O2 
EXEC=tutoriel3
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

LDLIBS   = -lglut -lGL -lGLU -lm -lpng


.PHONY:	run	clean

all: $(EXEC)

$(EXEC):$(OBJ) 
	$(GXX) $(LDFLAGS) -Wall -o $@ $^  $(LDLIBS)

%.o: %.cpp
	$(GXX)    -o $@    -c $< $(LDLIBS)

lib:
	$(GXX)    -o -DGLEW_BUILD -I./ -DGLEW_STATIC

run:	$(EXEC)
	./$(EXEC)

clean: 
	rm *.o *~ *# *.ppm


cleanall:
	rm *.o *~ *# ./$(EXEC)
