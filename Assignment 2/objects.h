#ifndef OBJ_H
#define OBJ_H 

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef double Matrix4x4 [4][4];

class point{
public:
    double x;
    double y;
    double z;
    point(double a,double b,double c){
    	x = a;
    	y = b;
    	z = c;
    }
    point(){
    	x = y = z = 0;
    }
};

const double PI = acos (-1);

class Object {
    inline float degreesToRadians (float degree) { return degree*PI/180; }

    void printTransformationMatrix (Matrix4x4 m); 
    void matrix4x4SetIdentity (Matrix4x4 matIdent4x4);
    void matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 m2, Matrix4x4 result);
    void translate3D (point P, Matrix4x4& matTransl3D);
    void rotate3D (point p1, point p2, float angleInDegrees, Matrix4x4 finalRotation);
    void printVector (vector<point> v);
    point multiplyMatrix (Matrix4x4 T, point p);

public:
	vector<point> points;
	void scale(double sx,double sy, double sz );
    void translate (point p);
    void rotate (point p1, point p2, float angle); 
	void shear(double shxy,double shxz,double shyx,
	double shyz,double shzx,double shzy);
	virtual void render();
};

class cube : public Object{
public:
	cube(point center,double side);
};

class sphere : public Object{
public:
	point center;
	double radius;
	sphere(point center,double radius );
};

#endif
