#include <GL/glut.h>
#include <cmath>
#include "objects.h"

#define VIEWING_DISTANCE_MIN  3.0
//point eye(0, 10, 0), coi(0, 0, 0), v_up(1, 0, 0);
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 0.5;
static GLfloat g_farPlane = 100;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static point vl(0, 100,0);  	   	   	   // Position of light
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

const GLdouble EFront[] = {0.0f, 0.0f, g_fViewDistance};
const GLdouble ERight[] = {g_fViewDistance, 0.0f, 0.0f};
const GLdouble ETop[]   = {0.0f, g_fViewDistance, 0.0};

const GLdouble VFront[] = {0,1,0};
const GLdouble VRight[] = {0,1,0};
const GLdouble VTop[]   = {1,0,0};

// EYE, CAMERA & NORMAL Settings
//point eye(0, 0, 10), coi(0, 0, 0), v_up(0, 1, 0);
point eye(EFront[0], EFront[1], EFront[2]), coi(0, 0, 0), v_up(VFront[0], VFront[1], VFront[2]);
//point eye(ETop[0], ETop[1], ETop[2]), coi(0, 0, 0), v_up(VTop[0], VTop[1], VTop[2]);
GLdouble ex=EFront[0], ey=EFront[1], ez=EFront[2];
//GLdouble ex=ERight[0], ey=ERight[1], ez=ERight[2];
//GLdouble ex=ETop[0], ey=ETop[1], ez=ETop[2];
GLdouble cx=0.5f, cy=0.5f, cz=0.5f;
GLdouble ux=0.0f, uy=1.0f, uz=0.0f;

GLfloat bottomCubeSize = 1.0f;
GLfloat bottomCubePos  = 2.5f;

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd')         rotate_y += rotate_step;
    else if (key == 'a')    rotate_y -= rotate_step;
    else if (key == 'w')    rotate_x += rotate_step;
    else if (key == 's')    rotate_x -= rotate_step;
    else if (key == 'q')    zoom *= (1.0 + zoom_step);
    else if (key == 'e')    zoom *= (1.0 - zoom_step);
    else if (key == '1')    bottomCubePos += 1;           // Push into the object 1
    else if (key == '2')    bottomCubePos -= 1;           // Pop out of the object 1
    else if (key == 'f')    { eye.x=EFront[0], eye.y=EFront[1], eye.z=EFront[2]; v_up.x=VFront[0]; v_up.y=VFront[1]; v_up.z=VFront[2];}
    else if (key == 'r')    { eye.x=ERight[0], eye.y=ERight[1], eye.z=ERight[2]; v_up.x=VRight[0]; v_up.y=VRight[1]; v_up.z=VRight[2];}
    else if (key == 't')    { eye.x=ETop[0],   eye.y=ETop[1],   eye.z=ETop[2];   v_up.x=VTop[0];   v_up.y=VTop[1];   v_up.z=VTop[2];  }

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

/*	cube home(point(),1);
	home.setColor (1,1,0);
	//home.worldToEye(eye, coi, v_up);
	//home.setPerspective (65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	//home.setLighting (Is, Ls, ambient, vp);
	//home.setViewPort (20, 100, 20, 100, 20, g_Width, 20, g_Height);
	//home.render(); 
	home.worldToEye(eye, coi, v_up);
	home.setOrtho(-1,1,-1,1,-1,1);
	home.projectFace();
	//home.glrender();
	home.glrenderProjected (0,2,0,2);
    //box.translate (point(0.2,0.2,0.2));
*/
	cube box(point(1,1,1),2);
	box.setColor (1,1,0);
	box.worldToEye(eye, coi, v_up);
	box.setOrtho(-1,1,-1,1,-1,1);
	//box.projectFace();
	//box.glrenderProjected (0,2,0,2);
    box.glrender ();
    box.calculateZMinZMax (0,2,0,2);
    cout << "BOX: zmin: " << box.zmin << " zmax: " << box.zmax << endl;
 
    double zmin=box.zmin, zmax=box.zmax;
    // RED PART
    cube redB(point(1,bottomCubePos+2*bottomCubeSize,1),bottomCubeSize);
	redB.setColor (1,0,0);  // RED COLOR
	redB.worldToEye(eye, coi, v_up);
	redB.setOrtho(-1,1,-1,1,-1,1);
	//redB.projectFace();
	redB.glrenderProjected (0,2,0,2, zmin, zmax);
    //redB.glrender ();

    // BLUE PART
    cube blueB(point(1,bottomCubePos+bottomCubeSize,1),bottomCubeSize);
	blueB.setColor (0,0,1); // B
	blueB.worldToEye(eye, coi, v_up);
	blueB.setOrtho(-1,1,-1,1,-1,1);
	blueB.glrenderProjected (0,2,0,2, zmin, zmax);
    //blueB.glrender();

    // GREEN PART
    cube greenB(point(1,bottomCubePos,1),bottomCubeSize);
	greenB.setColor (0,1,0);    // G
	greenB.worldToEye(eye, coi, v_up);
	greenB.setOrtho(-1,1,-1,1,-1,1);
	greenB.glrenderProjected (0,2,0,2, zmin, zmax);
    //greenB.glrender (); 

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


