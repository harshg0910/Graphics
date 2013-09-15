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


void Object::translate(){
	
}
void Object::rotate(){
	
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
	        double x = center.x + radius*cos(toRad(theta))*cos(toRad(phi));
	        double y = center.y + radius*sin(toRad(theta));
	        double z = center.z + radius*cos(toRad(theta))*sin(toRad(phi));
	        points.push_back(point(x,y,z));
        }
	}
}