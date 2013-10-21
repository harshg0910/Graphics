LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: objects.o intensity.o 
	$(CPP) intensity.o objects.o -o intensity $(LIB)

objects.o:objects.cpp objects.h
	$(CPP) -c objects.cpp -o objects.o 

intensity.o: intensityCalculation.cpp intensityCalculation.h objects.h
	$(CPP) -c intensityCalculation.cpp -o intensity.o 

clean:
	rm -rf intensity *.o
