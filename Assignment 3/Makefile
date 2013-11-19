LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: objects.o sol3.o sol4.o cube.o sphere.o 
	$(CPP) sol3.o -o sol3 $(LIB)
	$(CPP) sol4.o -o sol4 $(LIB)
	$(CPP) cube.o objects.o -o cube $(LIB)
	$(CPP) sphere.o objects.o -o sphere $(LIB)

sphere.o: sphere.cpp objects.h objects.cpp
	$(CPP) -c sphere.cpp -o sphere.o	

cube.o: cube.cpp objects.h objects.cpp
	$(CPP) -c cube.cpp -o cube.o	

sol3.o: sol3.cpp 
	$(CPP) -c sol3.cpp -o sol3.o

sol4.o: sol4.cpp 
	$(CPP) -c sol4.cpp -o sol4.o

objects.o:objects.cpp objects.h
	$(CPP) -c objects.cpp -o objects.o 

intensity.o: intensityCalculation.cpp intensityCalculation.h objects.h
	$(CPP) -c intensityCalculation.cpp -o intensity.o 

clean:
	rm -rf intensity *.o
