LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: sol-opengl.o clipping.o 
	$(CPP) sol-opengl.o -o sol-opengl $(LIB)
	$(CPP) clipping.o -o clipping $(LIB)

sol4-opengl.o: sol-opengl.cpp 
	$(CPP) -c sol-opengl.cpp -o sol-opengl.o

clipping.o: clipping.cpp 
	$(CPP) -c clipping.cpp -o clipping.o

clean:
	rm -rf sol-opengl *.o
