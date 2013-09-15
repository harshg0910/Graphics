#ifndef _VERTEX_LIST_H_
#define _VERTEX_LIST_H_

#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

#define CUBE_VERTICES   8

// Point representing the x,y,z coordinates 
typedef float Point3D [3];

// type declaration for the display function
typedef void (*displayFunc) ();

// type declaration for the display function
typedef void (*keyControl) (unsigned char, int, int);

// Type of objects supported by the library
enum TypeOfObject {
    TRIANGULAR_MESHES,
    TRIANGLE_MESH,
    TRIANGLE,
    CUBE,
    PLANE_MESH,
    CHULL_AND_TRIANGULATE,
    POLYGON
};


// Function which represents object using vertex list
void drawObjectGivenVertices (enum TypeOfObject typeOfObject, vector<Point3D> vertices, float color[3]);

void glutMainDefault (int argc, char** argv, string programName, displayFunc display, keyControl,int iWS[2], int iWP[2]);

// Initializer for GLUT system
void glutInitDefault ();

#endif
