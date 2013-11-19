#include <GL/glut.h>
#include <cmath>

#include "objects.h"
#define VIEWING_DISTANCE_MIN  3.0
point eye(0, 0, 1), coi(0, 0, 0), v_up(0, 1, 0);
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 0.5;
static GLfloat g_farPlane = 100;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static point vl(1, 1, -10);  	   	   // Position of light
static point vp(1,1,1);				   // Viewer's position
static Intensity ambient(0.1,0.02,0.02);
static Intensity light0(1.0,0,0);
vector<Intensity> Is(1, light0);
vector<point> Ls(1, vl);

// Clears the window and draws the torus.
void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    sphere tummy(point(),1.0);
    //tummy.worldToEye(eye, coi, v_up);
    //tummy.setPerspective (65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
    tummy.setLighting (Is, Ls, ambient, vp);

    tummy.render();

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
    glShadeModel(GL_SMOOTH);
    glutCreateWindow("A Scenario");
    glEnable(GL_DEPTH_TEST);
    glClearColor (1,1,1,0); // white
    glutDisplayFunc(display);

    glutMainLoop();
    return  0;
}


