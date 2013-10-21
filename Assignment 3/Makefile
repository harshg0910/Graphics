LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: objects.o intensity.o sol3.o sol4.o 
	$(CPP) intensity.o objects.o -o intensity $(LIB)
	$(CPP) sol3.o -o sol3 $(LIB)
	$(CPP) sol4.o -o sol4 $(LIB)

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
