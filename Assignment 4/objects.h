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

    void print() {
	cout << "x:" <<x;
	cout << "y:" <<y;
	cout << "z:" <<z << endl;
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

typedef point vector3;
struct SurfaceK {
	float KR;
	float KG;
        float KB;

	SurfaceK(float kR, float kG, float kB): KR(kR), KG(kG), KB(kB) {}
	SurfaceK(): KR(0), KG(0), KB(0) {}
};

struct Intensity {
	float IR;
	float IG;
	float IB;

	Intensity(): IR(0), IG(0), IB(0) {}
	Intensity(float iR, float iG, float iB): IR(iR), IG(iG), IB(iB) {}
	void intensityMulK(SurfaceK K) {
		IR *= K.KR; IG *= K.KG; IB *= K.KB;
	}
	
	Intensity operator+ (const Intensity& I) {
		Intensity Ir(IR, IG, IB);
		Ir.IR += I.IR;
		Ir.IG += I.IG;
		Ir.IB += I.IB;
		return Ir;
	}

	void print () {	
		cout << "Intensity: " << endl;
		cout << "R: " << IR << ", ";
		cout << "G: " << IG << ", ";
		cout << "B: " << IB << ", ";
		cout << endl;
	}
};

// Bronze Material Properties
const float DEFAULT_SHININESS=50.0;
const SurfaceK DEFAULT_AMBI (1.0, 1.0, 1.0);
const SurfaceK DEFAULT_DIFF (0.8, 0.6, 0.0);
const SurfaceK DEFAULT_SPEC ( 1.0, 1.0, 0.4);

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
	SurfaceK Ka, Kd, Ks;
	double ns;

	Matrix4x4 modelViewM;
	Matrix4x4 projectionM;
	Matrix4x4 viewPortM;

	GLfloat zCommon;	

	// World to Eye coordinates 
	void worldToEye (vector3 eye, vector3 coi, vector3 v_up);

	// Set the camera to this position with respective parameters
	void setPerspective(GLfloat fovy,GLfloat aspect,GLfloat zNear,GLfloat zFar);

	// Convert the window to view port
	void setViewPort (GLint vx1, GLint vx2, GLint vy1, GLint vy2,
		GLint wx1, GLint wx2, GLint wy1, GLint wy2);

	Object() {
		// BLUE color 
		color[0]=0.0; color[1]=0.0; color[2]=1.0;

		zCommon = 0;
		Ka = DEFAULT_AMBI;
		Ks = DEFAULT_SPEC;
		Kd = DEFAULT_DIFF;
		ns = DEFAULT_SHININESS;
		matrix4x4SetIdentity (modelViewM);
		matrix4x4SetIdentity (projectionM);
		matrix4x4SetIdentity (viewPortM);
	}

 	vector<point> points;
 	vector<point> normals;
	vector<Intensity> intensities;
	void printVector () { printVector(points); }
	point multiplyMatrix (Matrix4x4 T, point p);

	void setSurfaceK (SurfaceK ka, SurfaceK kd, SurfaceK ks, double s) {	
		Ka=ka; Kd=kd; Ks=ks;
		ns=s;
	}

	Intensity intensityAtP (Intensity Ia, vector<Intensity> Is, vector<point> Ls, point pP, point pN, point pV);
	
	Intensity intensityAtP (Intensity Il, point pP, point pL, point pN, point pV);

	void setColor (float r, float g, float b) {color[0]=r; color[1]=g; color[2]=b;}
	void scale(double sx,double sy, double sz );
	void translate (point p);
	void rotate (point p1, point p2, float angle); 
	void shear(double shxy,double shxz,double shyx,
			double shyz,double shzx,double shzy);
	virtual void render();
	bool setLight;
	vector<Intensity> Is;
	vector<point> Ls;
	Intensity ambient;
	point pV;

	void setLighting (vector<Intensity> is, vector<point> ls, Intensity amb, point v);
	void calcIntensities ();
};

typedef vector<point> face;
class cube : public Object {
    void pushFace (int x, int y, int z, int w);
public:
    vector<face> faces;
	cube(point center,double side);
	void render();
	void glrender();
};

class sphere : public Object{
public:
	point center;
	double radius;
	sphere(point center,double radius );
//	void render();
};

#endif
