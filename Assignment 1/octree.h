
typedef struct point{
    double x;
    double y;
    double z;
}point;

typedef struct color
{
    double red ;
    double green;
    double blue;
}color;

typedef struct cubeSideColor{
    color front;
    color back;
    color top;
    color bottom;
    color left;
    color right;
}cubeSideColor;
 


class octree{
	public:
		bool isSplit;
		point center;
		cubeSideColor colors;
		bool toPrint;
		double side;
		octree* child[8];
		octree(point center,cubeSideColor colors,double side,bool toPrint);
		octree* split();
		octree* getChild(int index);
};

void traverse(octree * oct,void(*render)(point,double,cubeSideColor) );