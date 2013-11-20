
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define VIEWING_DISTANCE_MIN  3.0

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static BOOL g_bLightingEnabled = TRUE;
static BOOL g_bFillPolygons = TRUE;
static BOOL g_bButton1Down = FALSE;
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

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

void RenderObjects(void)
{
  float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
  float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
  float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
  float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Main object (cube) ... transform to its coordinates, and render
  glRotatef(15, 1, 0, 0);
  glRotatef(45, 0, 1, 0);
  glRotatef(g_fTeapotAngle, 0, 0, 1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
  glColor4fv(colorBlue);
  DrawCube(1.0);

  // Child object (teapot) ... relative transform, and render
  glPushMatrix();
  glTranslatef(2, 0, 0);
  glRotatef(g_fTeapotAngle2, 1, 1, 0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
  glColor4fv(colorBronzeDiff);
  glutSolidTeapot(0.3);
//  glutSolidSphere(1,20,20);
  glPopMatrix(); 

  glPopMatrix();
}

void display(void)
{
   // Clear frame buffer and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set up viewing transformation, looking down -Z axis
   glLoadIdentity();
   gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

   // Set up the stationary light
   glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

   // Render the scene
   RenderObjects();

   // Make sure changes appear onscreen
   glutSwapBuffers();
}

void reshape(GLint width, GLint height)
{
   g_Width = width;
   g_Height = height;

   glViewport(0, 0, g_Width, g_Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
   glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}


int main(int argc, char** argv)
{
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (g_Width, g_Height);
  glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("CS248 GLUT example");

  // Initialize OpenGL graphics state
  InitGraphics();

  // Register callbacks:
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);

  // Turn the flow of control over to GLUT
  glutMainLoop ();
  return 0;
}

 


