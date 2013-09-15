#include <math.h>
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
	
} 

cube::cube(point center,double side){
	points.push_back(point(center.x - side/2.0 , center.y - side/2.0, center.z - side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y - side/2.0, center.z + side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y + side/2.0, center.z + side/2.0));
	points.push_back(point(center.x - side/2.0 , center.y + side/2.0, center.z - side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y - side/2.0, center.z - side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y - side/2.0, center.z + side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y + side/2.0, center.z + side/2.0));
	points.push_back(point(center.x + side/2.0 , center.y + side/2.0, center.z - side/2.0));
}

sphere::sphere(double rad ,point cen){
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