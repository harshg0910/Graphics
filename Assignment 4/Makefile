LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: sol-opengl.o clipping.o sol-3D.o objects.o cube.o sphere.o
	$(CPP) sol-opengl.o -o sol-opengl $(LIB)
	$(CPP) sol-3D.o -o sol-3D $(LIB)
	$(CPP) clipping.o -o clipping $(LIB)
	$(CPP) cube.o objects.o -o cube $(LIB)
	$(CPP) sphere.o objects.o -o sphere $(LIB)

sphere.o: sphere.cpp objects.h objects.cpp
	$(CPP) -c sphere.cpp -o sphere.o	

cube.o: cube.cpp objects.h objects.cpp
	$(CPP) -c cube.cpp -o cube.o	

objects.o:objects.cpp objects.h
	$(CPP) -c objects.cpp -o objects.o 

sol-opengl.o: sol-opengl.cpp 
	$(CPP) -c sol-opengl.cpp -o sol-opengl.o

sol-3D.o: sol-3D.cpp 
	$(CPP) -c sol-3D.cpp -o sol-3D.o

clipping.o: clipping.cpp 
	$(CPP) -c clipping.cpp -o clipping.o

clean:
	rm -rf sol-3D cube sphere clipping sol-opengl *.o
