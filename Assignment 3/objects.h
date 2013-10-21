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
    point(double a,double b,double c): x(a), y(b), z(c) {}
    point(): x(0), y(0), z(0) {}
    point(const point& p) : x(p.x), y(p.y), z(p.z) {}

    point operator-(const point& a) {
	point result;
	result.x = x-a.x;
	result.y = y-a.y;
	result.z = z-a.z;
	return result;
    }

    point cross(const point& v) {
	point result;
	result.x = y*v.z - z*v.y;
	result.y = z*v.x - x*v.z;
	result.z = x*v.y - y*v.x;
	return result;
    }

    double dot(const point& a) {
	point u(a), v(x,y,z);
	u.normalize();
	v.normalize();
	return u.x*v.x + u.y*v.y + u.z*v.z;
    }

    void scale(double mod) {
	x *= mod; y *= mod; z *= mod;
    }

    void normalize() {
	double mod = sqrt(x*x + y*y + z*z);
	x /= mod; y /= mod; z /= mod;
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

public:
	float color[3];

	Object() { color[0]=0.0; color[1]=0.0; color[2]=1.0; } // BLUE color 
	vector<point> points;
	void printVector () { printVector(points); }
	point multiplyMatrix (Matrix4x4 T, point p);
	void setColor (float r, float g, float b) {color[0]=r; color[1]=g; color[2]=b;}
	void scale(double sx,double sy, double sz );
	void translate (point p);
	void rotate (point p1, point p2, float angle); 
	void shear(double shxy,double shxz,double shyx,
			double shyz,double shzx,double shzy);
	virtual void render();
};

class cube : public Object {
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
