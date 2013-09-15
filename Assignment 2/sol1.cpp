#include <GL/glut.h>
#include <cmath>

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

    // Road
    cube road(point(),2);
    road.scale(1.0,0.0,10.0);
    road.render();   
    
/*
    point p1(0.0,0.0,0.0), p2(1.0,0.0,0.0);
    float angle=90.0;
    point p(-4.0, 0.0, 0.0);
    road.rotate (p1,p2,angle);
//    p2.x=0.0; p2.y=1.0;
//    road.rotate (p1,p2,angle);
    */
    // Home
    cube home(point(),4);
    home.translate(point(5.0,2,5.0));
    home.render(); 

    // Tree
    
    cube trunk(point(0.0,2,0.0),4);
    trunk.scale(0.25,1,0.25);
    sphere tree(point(0.0,5.0,0.0),2.0);
    tree.translate(point(-2.0,0,0));
    trunk.translate(point(-2.0,0,0));
    tree.render();
    trunk.render();   

    
    sphere tummy(point(),1.0);
    sphere head(point(0.0,1.0,0.0),0.25);
    tummy.scale(0.25,1.0,0.25);
    tummy.translate(point(3.0,0.75,-3.0));
    head.translate(point(3.0,0.5,-3.0));
    tummy.render();
    head.render();



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
    glutCreateWindow("A Simple Torus");
    glEnable(GL_DEPTH_TEST);
    glClearColor (1,1,1,0); // white
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return  0;
}


