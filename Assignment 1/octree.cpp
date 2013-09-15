#include "octree.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

octree::octree(point center,cubeSideColor colors,double side,bool toPrint){
	this->center = center;
	this->colors = colors;
	this->side = side;
	this->toPrint = toPrint;
	isSplit = false;
	for (int i = 0; i < 8; ++i)
	{
		(this->child)[i] = NULL;
	}
	
};

octree* octree::split(){
	if(isSplit)
		return this;
	
	isSplit = true;
	double x = center.x;
	double y = center.y;
	double z = center.z;
	double offset = side/4;
	point new_center;

	new_center.x = x+offset;
	new_center.y = y-offset;
	new_center.z = z+offset;
	child[0] = new octree(new_center,colors,side/2,true);

	new_center.x = x+offset;
	new_center.y = y-offset;
	new_center.z = z-offset; 
	child[1] = new octree(new_center,colors,side/2,true);

	new_center.x = x-offset;
	new_center.y = y-offset;
	new_center.z = z-offset; 
	child[2] = new octree(new_center,colors,side/2,true);

	new_center.x = x-offset;
	new_center.y = y-offset;
	new_center.z = z+offset; 
	child[3] = new octree(new_center,colors,side/2,true);

	new_center.x = x+offset;
	new_center.y = y+offset;
	new_center.z = z+offset; 
	child[4] = new octree(new_center,colors,side/2,true);

	new_center.x = x+offset;
	new_center.y = y+offset;
	new_center.z = z-offset; 
	child[5] = new octree(new_center,colors,side/2,true);

	new_center.x = x-offset;
	new_center.y = y+offset;
	new_center.z = z-offset; 
	child[6] = new octree(new_center,colors,side/2,true);

	new_center.x = x-offset;
	new_center.y = y+offset;
	new_center.z = z+offset; 
	child[7] = new octree(new_center,colors,side/2,true);
	return this;
}

octree* octree::getChild(int index){
	return child[index];
}

void traverse(octree * oct,void(*render)(point,double,cubeSideColor) ) {
	if(oct == NULL)
		return;
	else{
		if(oct->toPrint && !oct->isSplit) 
			render(oct->center,oct->side,oct->colors);
		for (int i = 0; i < 8; ++i)
		{
			traverse(oct->child[i],render);
		}
	}	
	
}
