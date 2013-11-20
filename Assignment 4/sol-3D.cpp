#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#define VIEWING_DISTANCE_MIN  3.0

// Global Variables
double rotate_y = 0.0;
double rotate_x = 0.0;
double zoom = 1.0;
const double rotate_step = 5.0;
const double zoom_step = 0.01;

static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height

GLfloat bottomCubeSize = 0.6f;
GLfloat bottomCubePos  = 0.6f;

// toggle each of 3 clipping planes
GLboolean g_clip1 = GL_FALSE;
GLboolean g_clip2 = GL_FALSE;
GLboolean g_clip3 = GL_FALSE;

// clipping planes
GLdouble eqn1[4] = { 1.0, 0.0, 0.0, 0.0 };
GLdouble eqn2[4] = { 0.0, 1.0, 0.0, 0.0 };
GLdouble eqn3[4] = { 0.0, 0.0, 1.0, 0.0 };

// translation for the clipping planes
GLfloat g_clip_x = 0.0f;
GLfloat g_clip_y = 0.0f;
GLfloat g_clip_z = 0.0f;

void DrawCubeFace(float fSize)
{
  fSize /= 2.0;
  glBegin(GL_QUADS);
  glVertex3f(-fSize, -fSize, fSize); 
  glVertex3f(fSize, -fSize, fSize); 
  glVertex3f(fSize, fSize, fSize); 
  glVertex3f(-fSize, fSize, fSize);
  glEnd();
}

void DrawCube (float fSize)
{
  glPushMatrix();
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 0, 1, 0);
  DrawCubeFace (fSize);
  glRotatef (180, 0, 1, 0);
  DrawCubeFace (fSize);
  glPopMatrix();
}

void DrawCubeBoundary(float fSize)
{
  fSize /= 2.0;
  glBegin(GL_LINE_LOOP);
  glVertex3f(-fSize, -fSize, fSize); 
  glVertex3f(fSize, -fSize, fSize); 
  glVertex3f(fSize, fSize, fSize); 
  glVertex3f(-fSize, fSize, fSize);
  glEnd();
}

void DrawBoundary (float fSize) {
  glPushMatrix();
  DrawCubeBoundary (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeBoundary (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeBoundary (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeBoundary (fSize);
  glRotatef (90, 0, 1, 0);
  DrawCubeBoundary (fSize);
  glRotatef (180, 0, 1, 0);
  DrawCubeBoundary (fSize);
  glPopMatrix();
}

void RenderObjects(void)
{
  float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
  float colorRed[4]        = { 1.0, 0.0, 0.0, 1.0 };
  float colorGreen[4]      = { 0.0, 1.0, 0.0, 1.0 };
  float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
	  //glTranslatef(-3, -2, 0);
	  //glRotatef(15, 1, 0, 0);
	  //glRotatef(60, 0, 1, 0);
	  glColor4fv(colorBlue);
	  DrawBoundary(1.0);

	  glTranslatef(0, bottomCubePos, 0);
	  glColor4fv(colorGreen);
	  DrawCube(bottomCubeSize);

	  glTranslatef(0, bottomCubeSize, 0);
	  glColor4fv(colorBlue);
	  DrawCube(bottomCubeSize);

	  glTranslatef(0, bottomCubeSize, 0);
	  glColor4fv(colorRed);
	  DrawCube(bottomCubeSize);
  glPopMatrix();
}

const GLdouble EFront[] = {0.0f, 0.0f, g_fViewDistance};
const GLdouble ERight[] = {g_fViewDistance, 0.0f, 0.0f};
const GLdouble ETop[]   = {0.0f, g_fViewDistance, 0.0};

// EYE, CAMERA & NORMAL Settings
GLdouble ex=EFront[0], ey=EFront[1], ez=EFront[2];
//GLdouble ex=ERight[0], ey=ERight[1], ez=ERight[2];
//GLdouble ex=ETop[0], ey=ETop[1], ez=ETop[2];
GLdouble cx=0.5f, cy=0.5f, cz=0.5f;
GLdouble ux=0.0f, uy=1.0f, uz=0.0f;

void display(void)
{
   // Clear frame buffer and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor (1,1,1,0);

   // Set up viewing transformation, looking down -Z axis
   //glLoadIdentity();
   //gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz);
   glRotatef(rotate_x, 1.0, 0.0, 0.0);
   glRotatef(rotate_y, 0.0, 1.0, 0.0);
   glScaled(zoom, zoom, zoom);
   //gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

 // Draw a red x-axis, a green y-axis, and a blue z-axis. Each of the
 // axes are ten units long.
   glBegin(GL_LINES);
   glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
   glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
   glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
   glEnd();

   // Render the scene
   RenderObjects();

   // Make sure changes appear onscreen
   glutSwapBuffers();
}

void reshape(GLint width, GLint height)
{
  // cout << "RESHAPE called" << endl;
   g_Width = width;
   g_Height = height;

   glViewport(0, 0, g_Width, g_Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
/*   double w = glutGet( GLUT_WINDOW_WIDTH );
   double h = glutGet( GLUT_WINDOW_HEIGHT );
   double ar = w / h;
   glOrtho( -ar/2, ar/2, -0.5, 0.5, 0.0, 1); */
   gluPerspective(60.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
//   gluOrtho2D (-1,2,-1,2);

/*   const int L = 3;
   if (width<=height)
	gluOrtho2D (-L, L, -L*height/width, L* height/width);
   else
	gluOrtho2D (-L*width/height, L*width/height, -L, L); */

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity( );
   gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz);
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 'd')         rotate_y += rotate_step;
    else if (key == 'a')    rotate_y -= rotate_step;
    else if (key == 'w')    rotate_x += rotate_step;
    else if (key == 's')    rotate_x -= rotate_step;
    else if (key == 'q')    zoom *= (1.0 + zoom_step);
    else if (key == 'e')    zoom *= (1.0 - zoom_step);
    else if (key == '1')    bottomCubePos += 0.2;           // Push into the object 1
    else if (key == '2')    bottomCubePos -= 0.2;           // Pop out of the object 1
    else if (key == 'f')    { ex=EFront[0], ey=EFront[1], ez=EFront[2]; }
    else if (key == 'r')    { ex=ERight[0], ey=ERight[1], ez=ERight[2]; }
    else if (key == 't')    { ex=ETop[0], ey=ETop[1], ez=ETop[2];       }

    // do a reshape since g_eye_y might have changed
    reshape(g_Width, g_Height);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (g_Width, g_Height);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("OpenGL Clipping, HSR, & Scan Conversion");

  glEnable (GL_DEPTH_TEST);

  // Register callbacks:
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc(keyboardFunc);

  // Turn the flow of control over to GLUT
  glutMainLoop ();
  return 0;
}
