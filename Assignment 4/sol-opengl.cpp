#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#define VIEWING_DISTANCE_MIN  3.0

static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height

GLfloat bottomCubeSize = 0.6f;
GLfloat bottomCubePos  = 0.6f;

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

void display(void)
{
   // Clear frame buffer and depth buffer
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor (1,1,1,0);
   glClear(GL_COLOR_BUFFER_BIT);

   // Set up viewing transformation, looking down -Z axis
   //glLoadIdentity();
   //gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

   // Render the scene
   RenderObjects();

   // Make sure changes appear onscreen
   glutSwapBuffers();
}

GLdouble ex=0.0f, ey=0.0f, ez=g_fViewDistance;
GLdouble cx=0.5f, cy=0.5f, cz=0.5f;
GLdouble ux=0.0f, uy=1.0f, uz=0.0f;

void reshape(GLint width, GLint height)
{
  // cout << "RESHAPE called" << endl;
   g_Width = width;
   g_Height = height;

   glViewport(0, 0, g_Width, g_Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
//   gluPerspective(60.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
//   gluOrtho2D (-1,2,-1,2);

   const int L = 3;
   if (width<=height)
	gluOrtho2D (-L, L, -L*height/width, L* height/width);
   else
	gluOrtho2D (-L*width/height, L*width/height, -L, L);

   glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity( );
   //gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz);
}

void keyboardFunc( unsigned char key, int x, int y )
{
    switch( key )
    {
	case '1':
		bottomCubePos += 0.2;
		break;
	case '2':
		bottomCubePos -= 0.2;
		break;
    }

    // do a reshape since g_eye_y might have changed
    //reshape(g_Width, g_Height);
    glutPostRedisplay( );
}

int main(int argc, char** argv)
{
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (g_Width, g_Height);
  //glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow ("OpenGL Clipping, HSR, & Scan Conversion");

  // Register callbacks:
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc(keyboardFunc);

  // Turn the flow of control over to GLUT
  glutMainLoop ();
  return 0;
}
