#include <GL/glut.h>
#include <cmath>
#include "objects.h"

#define VIEWING_DISTANCE_MIN  3.0
point eye(0, 0, 10), coi(0, 0, 0), v_up(0, 1, 0);
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 0.5;
static GLfloat g_farPlane = 100;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static point vl(0, 100,0);  	   	   // Position of light
static point vp(1,1,1);				   // Viewer's position
static Intensity ambient(0.1,0.02,0.02);
static Intensity light0(1.0,1.0,1.0);
vector<Intensity> Is(1, light0);
vector<point> Ls(1, vl);

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

	cube home(point(),1);
	home.worldToEye(eye, coi, v_up);
	home.setPerspective (65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	home.setLighting (Is, Ls, ambient, vp);
	//home.setViewPort (20, 100, 20, 100, 20, g_Width, 20, g_Height);
	home.render(); 

	sphere tummy(point(1,2,0),1);
	tummy.worldToEye(eye, coi, v_up);
	tummy.setPerspective (65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
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
	glutCreateWindow("A Scenario");
	glEnable(GL_DEPTH_TEST);
	gluLookAt(3, 4, 5, 0, 0, 0, 0, 1,0);
	glClearColor (1,1,1,0); // white
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return  0;
}


