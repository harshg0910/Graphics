#include <GL/glut.h>
#include <cmath>

#include "objects.h"

#define toRad(a) a*3.14/180

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;
double zoom              = 1.0;
const double rotate_step = 5.0;
const double zoom_step   = 0.01;

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


    sphere s(1,point());
   
    glBegin(GL_POINTS);
    s.shear(1.0, 0.0, 0, 0, 0, 0);
    for(unsigned int i = 0 ; i < s.points.size() ; i++){
        point p = s.points[i];
        glVertex3f(p.x,p.y,p.z);
    }
    glEnd();

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


