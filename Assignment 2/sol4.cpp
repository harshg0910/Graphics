#include <GL/glut.h>
#include <cmath>

#include "vertexList.h"
#include "objects.h"

#define toRad(a) a*3.14/180

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;
double zoom              = 0.1;
const double rotate_step = 5.0;
const double zoom_step   = 0.1;

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd')
        rotate_y += rotate_step;
    else if (key == 'a')
        rotate_y -= rotate_step;
    else if (key == 'w')
        rotate_x += rotate_step;
    else if (key == 's')
        rotate_x -= rotate_step;
    else if (key == 'q')
        zoom *= (1.0 + zoom_step);
    else if (key == 'e')
        zoom *= (1.0 - zoom_step);

    glutPostRedisplay();
}


void cube(point center,double side) {
    double half_side = side / 2.0;
    double front     = center.z + half_side;
    double back      = center.z - half_side;
    double right     = center.x + half_side;
    double left      = center.x - half_side;
    double top       = center.y + half_side;
    double bottom    = center.y - half_side;

    float p[8][3];
    p[0][0] = left;  p[0][1]=top; 	p[0][2]=front;  
    p[1][0] = right; p[1][1]=top; 	p[1][2]=front; 
    p[2][0] = right; p[2][1]=bottom; 	p[2][2]=front; 
    p[3][0] = left;  p[3][1]=bottom;	p[3][2]=front;
    p[4][0] = left;  p[4][1]=top; 	p[4][2]=back;  
    p[5][0] = right; p[5][1]=top; 	p[5][2]=back;  
    p[6][0] = right; p[6][1]=bottom; 	p[6][2]=back;  
    p[7][0] = left;  p[7][1]=bottom; 	p[7][2]=back;  

    float color[3] = {1.0, 0.5, 0.2};
    vector<Point3D> cubeV(&p[0], &p[0]+8);
    drawObjectGivenVertices (CUBE, cubeV, color);
}

// Clears the window and draws the torus.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glScaled(zoom, zoom, zoom);

    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    // start ROAD
    float roadVerticesM[][3] = 
	{
	        {1.0f, 0.0f, 10.0f},
	        {-1.0f, 0.0f, 10.0f},
	        {-1.0f, 0.0f, -10.0f},
        	{1.0f, 0.0f, -10.0f}
	};
    vector<Point3D> roadVertices (&roadVerticesM[0], &roadVerticesM[0]+4);
    float color[3] = {1.0, 0.5, 0.2};
    drawObjectGivenVertices (POLYGON, roadVertices, color);
    // end ROAD

    // Home
    // THIS IS NOT HOME ;)
    cube(point(5.0,2,5.0),4);

    // Tree
    glPushMatrix ();
    glTranslatef (-2.0,0,0);
    glScaled(0.25,1,0.25);
    cube(point(0.0,2.0,0.0),4);
    glScaled(4,1,4);
    glTranslatef (0.0,5.0,0.0);
    cube(point(0.0,0.0,0.0),2.4);	// tree head
    //glutSolidSphere(2, 20, 20);
    glPopMatrix (); 
 
    // Body
    glPushMatrix ();
    glTranslatef (3.0,0.75,-3.0);
    glScaled(0.25,1,0.25);
    cube(point(0.0,0.0,0.0),1.4);	// andriod body
    //glutSolidSphere(1, 20, 20);
    glPopMatrix (); 

    // head
    glPushMatrix ();
    glTranslatef (3.0,1.5,-3.0);
    cube(point(0.0,0.0,0.0),0.2);	// andriod head
   // glutSolidSphere(0.25, 20, 20);
    glPopMatrix (); 

    // hands
    cube(point(3.0,0.75,-3.0),0.4);

    // legs
    cube(point(3.0,-0.2,-3.0),0.4);

    glFlush();
    glutSwapBuffers();
}



// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(80, 80);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("A Scenario");
    glEnable(GL_DEPTH_TEST);
    glClearColor (1,1,1,0); // white
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return  0;
}


