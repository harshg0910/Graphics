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

  /*  // Road
    cube road(point(),2);
    //s.shear(1.0,0.0,0.0,0.0,0.0,0.0);
    road.scale(1.0,0.0,10.0);
    road.render();   
    */
    // Home
    cube home(point(5.0,2,5.0),4);
    home.render();   

    // Tree
    /*
    cube trunk(point(0.0,2,0.0),4);
    trunk.scale(0.25,1,0.25);
    trunk.render();   
    sphere tree(point(0.0,5.0,0.0),2.0);
    tree.render();
*/
    sphere tummy(point(),1.0);
    tummy.scale(0.5,1.0,0.5);
    sphere head(point(0.0,1.0,0.0),0.25);
    tummy.scale(0.5,1.0,0.5);

    /*cube leg1(point(0.0,2,0.0),4);
    leg1.scale(0.25,1,0.25);
    
    cube leg2(point(0.0,2,0.0),4);
    leg2.scale(0.25,1,0.25);
    
    cube hand1(point(0.0,2,0.0),4);
    hand1.scale(0.25,1,0.25);
    
    cube hand2(point(0.0,2,0.0),4);
    hand2.scale(0.25,1,0.25);
*/
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
    glClearColor (0,0,0,0); // white
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return  0;
}


