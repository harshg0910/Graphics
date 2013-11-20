#include <stdio.h>
#include <GL/glut.h>

#define VIEWING_DISTANCE_MIN  3.0

static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height

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
	  glRotatef(60, 0, 1, 0);
	  //glRotatef(g_fTeapotAngle, 0, 0, 1); 
	  glColor4fv(colorBlue);
	  DrawBoundary(1.0);

	  glTranslatef(0, 1, 0);
	  glColor4fv(colorGreen);
	  DrawCube(1.0);

	  glTranslatef(0, 1, 0);
	  glColor4fv(colorBlue);
	  DrawCube(1.0);

	  glTranslatef(0, 1, 0);
	  glColor4fv(colorRed);
	  DrawCube(1.0);
  glPopMatrix();
}

void display(void)
{
   // Clear frame buffer and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set up viewing transformation, looking down -Z axis
   glLoadIdentity();
   gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);

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
   gluPerspective(60.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
//   glOrtho(0.0f, g_Width, 0.0f, g_Height, -1.0f, 1.0f);
   //glOrtho (0.0, g_Width, 0.0, g_Height, g_nearPlane, g_farPlane);
   glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
}

int main(int argc, char** argv)
{
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (g_Width, g_Height);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("OpenGL Clipping, HSR, & Scan Conversion");

  // Initialize OpenGL graphics state
  InitGraphics();

  // Register callbacks:
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);

  // Turn the flow of control over to GLUT
  glutMainLoop ();
  return 0;
}
