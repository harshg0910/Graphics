LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: sol-opengl.o clipping.o sol-3D.o
	$(CPP) sol-opengl.o -o sol-opengl $(LIB)
	$(CPP) sol-3D.o -o sol-3D $(LIB)
	$(CPP) clipping.o -o clipping $(LIB)

sol4-opengl.o: sol-opengl.cpp 
	$(CPP) -c sol-opengl.cpp -o sol-opengl.o

sol3-3D.o: sol-3D.cpp 
	$(CPP) -c sol-3D.cpp -o sol-3D.o

clipping.o: clipping.cpp 
	$(CPP) -c clipping.cpp -o clipping.o

clean:
	rm -rf sol-opengl *.o
