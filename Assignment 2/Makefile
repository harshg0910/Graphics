LIB = -lGL -lGLU -lglut
CPP = g++ -Wall

all: sol1.cpp objects.o 
	$(CPP) sol1.cpp objects.o -o sol1 $(LIB)
	$(CPP) solution4.cpp -o sol4 $(LIB)


objects.o:objects.cpp objects.h
	$(CPP) -c objects.cpp -o objects.o 

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
	rm -rf sol1 vertexList.o sol3-vertexList sol3-octree sol4 *.o
