#include <GL/glut.h>
#include <cmath>
#include "objects.h"

#define toRad(a) a*3.14/180

using namespace std;

void Object::scale(double sx,double sy, double sz ){
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		points[i].x = points[i].x * sx;
		points[i].y = points[i].y * sy;
		points[i].z = points[i].z * sz;
	}
}

void Object::printTransformationMatrix (Matrix4x4 m) {
    cout << "\n Translation matrix looks like " << endl;
    for (int row=0; row<4; row++) {
        for (int col=0; col<4; col++) 
            cout << " "<< m[row][col] << "->";
        cout << endl;
    }
}

void Object::matrix4x4SetIdentity (Matrix4x4 matIdent4x4) {
    for (int row=0; row<4; row++)
        for (int col=0; col<4; col++)
            matIdent4x4[row][col] = row==col;
}

void Object::matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 m2, Matrix4x4 result) {
    Matrix4x4 tmp;
    for (int row=0; row<4; row++)
        for (int col=0; col<4; col++) {
            tmp[row][col] = 0;
            for (int i=0; i<4; i++)
                tmp[row][col] += m1[row][i] * m2[i][col];
        }

    for (int row=0; row<4; row++)
        for (int col=0; col<4; col++) 
            result[row][col] = tmp[row][col];
}

void Object::translate3D (point P, Matrix4x4& matTransl3D) {
    matrix4x4SetIdentity (matTransl3D);
    matTransl3D[0][3] = P.x;
    matTransl3D[1][3] = P.y;
    matTransl3D[2][3] = P.z;
}

void Object::rotate3D (point p1, point p2, float angleInDegrees, Matrix4x4 finalRotation) {
    float angle = degreesToRadians (angleInDegrees);
    float a=p2.x-p1.x, b=p2.y-p1.y, c=p2.z-p1.z;
    float d = sqrt(b*b + c*c);
    Matrix4x4 matTranslationForward;
    Matrix4x4 matRotateToXZ, matRotateToZ;
    Matrix4x4 matRotateAngle;

    matrix4x4SetIdentity (finalRotation);

    // translate x,y,z to origin T 
    point pMinus;
    pMinus.x=-1*p1.x; pMinus.y=-1*p1.y; pMinus.z=-1*p1.z;
    translate3D (pMinus, matTranslationForward);

    // Rotate  line such that now it lies in XZ plane RxA
    matrix4x4SetIdentity (matRotateToXZ);
    if (d>0) {
        matRotateToXZ[1][1] = matRotateToXZ[2][2] = c/d;
        matRotateToXZ[1][2] = -1*b/d;
        matRotateToXZ[2][1] = b/d;
    }

#ifdef _DEBUG_
    cout << "rotation xz" << endl;
    printTransformationMatrix (matRotateToXZ);
#endif
    // F = RxA x T
    matrix4x4PreMultiply (matRotateToXZ, matTranslationForward, finalRotation);

    // Rotate line from XZ to Z plane RyB
    matrix4x4SetIdentity (matRotateToZ);
    matRotateToZ[0][0] = matRotateToZ[2][2] = d;
    matRotateToZ[0][2] = -1*a;
    matRotateToZ[2][0] = a;

#ifdef _DEBUG_
    cout << "rotation z" << endl;
    printTransformationMatrix (matRotateToZ);
#endif
    // F = RyB x RxA x T
    matrix4x4PreMultiply (matRotateToZ, finalRotation, finalRotation);

    // rotate about angle around z-axis RTheta
    matrix4x4SetIdentity (matRotateAngle);
    matRotateAngle[0][0] = matRotateAngle[1][1] = cos(angle);
    matRotateAngle[0][1] = sin(angle);
    matRotateAngle[1][0] = -1*sin(angle);

#ifdef _DEBUG_
    cout << "rotation theta" << endl;
    printTransformationMatrix (matRotateAngle);
#endif
    // F = RTheta x RyB x RxA x T
    matrix4x4PreMultiply (matRotateAngle, finalRotation, finalRotation);

    // Rotate back from Z plane to XZ plane initial line position RyB-1
    matrix4x4SetIdentity (matRotateToZ);
    matRotateToZ[0][0] = matRotateToZ[2][2] = d;
    matRotateToZ[0][2] = a;
    matRotateToZ[2][0] = -1*a;

#ifdef _DEBUG_
    cout << "rotation z" << endl;
    printTransformationMatrix (matRotateToZ);
#endif
    // F = RyB-1 x RTheta x RyB x RxA x T
    matrix4x4PreMultiply (matRotateToZ, finalRotation, finalRotation);

    // Rotate line from XZ plane back to its original position RxA-1
    matrix4x4SetIdentity (matRotateToXZ);
    if (d>0) {
        matRotateToXZ[1][1] = matRotateToXZ[2][2] = c/d;
        matRotateToXZ[1][2] = -1*b/d;
        matRotateToXZ[2][1] = b/d;
    }

#ifdef _DEBUG_
    cout << "rotation xz" << endl;
    printTransformationMatrix (matRotateToXZ);
#endif

    // F = RxA-1 x RyB-1 x RTheta x RyB x RxA x T
    matrix4x4PreMultiply (matRotateToXZ, finalRotation, finalRotation);

    // translate back x,y,z from origin to x,y,z T-1
    translate3D (p1, matTranslationForward);

    // F = T-1 x RxA-1 x RyB-1 x RTheta x RyB x RxA x T
    matrix4x4PreMultiply (matTranslationForward, finalRotation, finalRotation);
}

void Object::printVector (vector<point> v) {
    cout << "\n start print vector v" << endl;
    for (size_t i=0; i<v.size(); i++) cout << v[i].x << "," << v[i].y << "," << v[i].z << "-->" ;
    cout << "\n end print vector v" << endl;
}

point Object::multiplyMatrix (Matrix4x4 T, point p) {
    point ret;
    ret.x = T[0][0]*p.x + T[0][1]*p.y + T[0][2]*p.z + T[0][3];
    ret.y = T[1][0]*p.x + T[1][1]*p.y + T[1][2]*p.z + T[1][3];
    ret.z = T[2][0]*p.x + T[2][1]*p.y + T[2][2]*p.z + T[2][3];
    return ret;
}

void Object::translate (point P) {
    // get the translation matrix for this point P
    Matrix4x4 translationMatrix;
    translate3D (P, translationMatrix);

#ifdef _DEBUG_
    printTransformationMatrix (translationMatrix);
    cout << "Translating origin to point P(" << P.x << "," << P.y << "," << P.z << ")" << endl;
    printVector(points);
#endif
    for (size_t i=0; i<points.size (); i++) 
        points[i] = multiplyMatrix (translationMatrix, points[i]);
}

void Object::rotate (point p1, point p2, float angle) {
    // get the translation matrix for this point P
    Matrix4x4 rotationMatrix;
    rotate3D (p1, p2, angle, rotationMatrix);

#ifdef _DEBUG_
    cout << "Rotating about P1 and P2" << endl;
    printVector(points);
#endif
    for (size_t i=0; i<points.size (); i++) 
        points[i] = multiplyMatrix (rotationMatrix, points[i]);
}

void Object::shear(double shxy,double shxz,double shyx,
	double shyz,double shzx,double shzy){
	
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		double x = points[i].x + points[i].y * shxy + points[i].z * shxz;
		double y = points[i].y + points[i].x * shyx + points[i].z * shyz;
		double z = points[i].z + points[i].x * shzx + points[i].y * shzy;
		
		points[i].x = x;
		points[i].y = y;
		points[i].z = z;
	}

}

void Object::render(){
	glBegin(GL_POINTS);
    for(unsigned int i = 0 ; i < points.size() ; i++){
        point p = points[i];
        glVertex3f(p.x,p.y,p.z);
    }
    glEnd();
} 

cube::cube(point center,double side){
	
	// For front and back faces
	double i = center.x - side/2.0;
	for (double j = center.y - side/2.0; j <= center.y + side/2.0; j += 0.01)
	{
		for (double k = center.z - side/2.0; k <= center.z + side/2.0; k += 0.01)
		{
			points.push_back(point(i,j,k));
		}
	}
	i = center.x + side/2.0;
	for (double j = center.y - side/2.0; j <= center.y + side/2.0; j += 0.01)
	{
		for (double k = center.z - side/2.0; k <= center.z + side/2.0; k += 0.01)
		{
			points.push_back(point(i,j,k));
		}
	}

	// For left and right faces
	i = center.y - side/2.0;
	for (double j = center.x - side/2.0; j <= center.x + side/2.0; j += 0.01)
	{
		for (double k = center.z - side/2.0; k <= center.z + side/2.0; k += 0.0100)
		{
			points.push_back(point(j,i,k));
		}
	}
	i = center.y + side/2.0;
	for (double j = center.x - side/2.0; j <= center.x + side/2.0; j += 0.01)
	{
		for (double k = center.z - side/2.0; k <= center.z + side/2.0; k += 0.01)
		{
			points.push_back(point(j,i,k));
		}
	}

	// For top and bottom faces
	i = center.z - side/2.0;
	for (double j = center.y - side/2.0; j <= center.y + side/2.0; j += 0.01)
	{
		for (double k = center.x - side/2.0; k <= center.x + side/2.0; k += 0.01)
		{
			points.push_back(point(k,j,i));
		}
	}
	i = center.z + side/2.0;
	for (double j = center.y - side/2.0; j <= center.y + side/2.0; j += 0.01)
	{
		for (double k = center.x - side/2.0; k <= center.x + side/2.0; k += 0.01)
		{
			points.push_back(point(k,j,i));
		}
	}

	/*
	points.push_back(point(center.x - side/2.0 , center.y - side/2.0, center.z - side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y - side/2.0, center.z + side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y + side/2.0, center.z + side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y + side/2.0, center.z - side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y - side/2.0, center.z - side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y - side/2.0, center.z + side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y + side/2.0, center.z + side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y + side/2.0, center.z - side/2.0));
	*/
}

sphere::sphere(point cen,double rad ){
	center = cen;
	radius = rad;
    for(double theta = -90.0; theta < 90.0 ; theta++ ){
	    for(int phi=0 ;phi < 360 ; phi++) {
	        double x = radius*cos(toRad(theta))*cos(toRad(phi));
	        double y = radius*sin(toRad(theta));
	        double z = radius*cos(toRad(theta))*sin(toRad(phi));
	        points.push_back(point(x,y,z));
        }
	}
}
