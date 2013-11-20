#include <GL/glut.h>
#include <cmath>

// Global Variables
#define TRUE 1
#define FALSE 0
#define VIEWING_DISTANCE_MIN  3.0

static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 90.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 800;                          // Initial window width
static int g_Height = 800;                         // Initial window height
static float g_lightPos[4] = { 0, 100, 0, 1 };  // Position of light

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
  float colorRed[4]        = { 1.0, 0.0, 0.0, 1.0 };


  glMatrixMode(GL_MODELVIEW);
    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    //glPushMatrix();
  glPushMatrix();
    glBegin(GL_LINES);
   // glRotatef(45, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();
  glPopMatrix();

 // Child object (teapot) ... relative transform, and render
  glPushMatrix();
  glTranslatef(2, 0, 0);
 // glRotatef(g_fTeapotAngle2, 1, 1, 1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
  glColor4fv(colorBronzeDiff);
  glutSolidTeapot(1);
  //glutSolidSphere(1,20,20);
  glPopMatrix();  


  glPushMatrix();
  // Main object (cube) ... transform to its coordinates, and render
  glTranslatef(-2, 0, 0);
  //glRotatef(15, 1, 0, 0);
  //glRotatef(45, 0, 1, 0);
  //glRotatef(g_fTeapotAngle, 0, 0, 1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
  glMaterialfv(GL_FRONT, GL_SPECULAR, colorRed);
  glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
  glColor4fv(colorBlue);
  DrawCube (1.0);
  glPopMatrix();

 }

void display(void)
{
   // Clear frame buffer and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set up viewing transformation, looking down -Z axis
   glLoadIdentity();

   
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    // Set up the stationary light
    glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

    // Render the scene
    RenderObjects();
    glFlush();
   // Make sure changes appear onscreen
   glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
   g_Width = width;
   g_Height = height;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
   glMatrixMode(GL_MODELVIEW);
   glViewport(0, 0, g_Width, g_Height);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(80, 80);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Shading in OpenGL");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor (1,1,1,0); // white
    glutDisplayFunc(display);
    glutReshapeFunc (reshape);
    //glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


