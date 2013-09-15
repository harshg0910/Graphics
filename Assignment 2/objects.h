#ifndef OBJ_H
#define OBJ_H 

#include <GL/glut.h>
#include <vector>

using namespace std;

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

class Object{
public:
	vector<point> points;
	void scale(double sx,double sy, double sz );
	void translate();
	void rotate();
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