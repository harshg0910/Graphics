LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: sol3.cpp objects.o cube.cpp sphere.cpp sol5.cpp vertexList.o
	$(CPP) sol3.cpp objects.o -o sol3 $(LIB)
	$(CPP) cube.cpp objects.o -o cube $(LIB)
	$(CPP) sphere.cpp objects.o -o sphere $(LIB)
	$(CPP) sol5.cpp -o sol5 $(LIB)
	$(CPP) sol4.cpp vertexList.o -o sol4 $(LIB)


objects.o:objects.cpp objects.h
	$(CPP) -c objects.cpp -o objects.o 

vertexList.o: vertexList.cpp vertexList.h
	$(CPP) -c vertexList.cpp -o vertexList.o 

# all: vertexList sol3V sol1.cpp sol3-octreeObject.o octree.o sol4.cpp
# 	$(CPP) sol1.cpp -o sol1 $(LIB)
# 	$(CPP) sol3-octreeObject.o octree.o -o sol3-octree $(LIB)
# 	$(CPP) sol4.cpp vertexList.o -o sol4 $(LIB)

# sol3V: vertexList
# 	$(CPP) sol3-vertexList.cpp vertexList.o -o sol3-vertexList $(LIB)

# vertexList:
# 	$(CPP) -c vertexList.cpp -o vertexList.o 

# sol3-octreeObject.o: sol3-octreeObject.cpp octree.h
# 	g++ -Wall -c sol3-octreeObject.cpp -o sol3-octreeObject.o 

# octree.o: octree.cpp octree.h
# 	g++ -Wall -c octree.cpp -o octree.o

clean:
	rm -rf cube sphere sol3 sol4 sol5 *.o
