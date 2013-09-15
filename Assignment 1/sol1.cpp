#include <GL/glut.h>
#include <cmath>

#define toRad(a) a*3.14/180
int square[4][2] = {{3,3}, {0,3}, {0,0}, {3,0}};

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

    // Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
    // and 30 slices.
    glColor3f(1.0, 1.0, 1.0);
    glutWireTorus(0.5, 3, 15, 30);

    // WireSphere
    glPushMatrix ();
    glTranslatef (3.0, 3.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(0.75, 20, 20);
    glPopMatrix (); 

    // Square
    glBegin (GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2iv (square[0]);
    glVertex2iv (square[1]);
    glVertex2iv (square[2]);
    glVertex2iv (square[3]);
    glEnd ();

    // Top-face
    glBegin(GL_QUADS); // of the color cube
    glColor3f(0.0f, 1.0f, 0.0f); // green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom-face
    glColor3f(1.0f, 0.5f, 0.0f); // orange
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Front-face
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back-face
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left-face
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right-face
    glColor3f(1.0f, 0.0f, 1.0f); // magenta
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd(); // of the color cube 


    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    // WireSphere, BOUNDARY REPRESENTATION
    glPushMatrix ();
    glTranslatef (1.0, -0.5, 2.8);
    glutWireSphere (0.7, 2.0, 7.6);
    glPopMatrix ();

    // Tetrahedron
    glPushMatrix ();
    glColor3f (0.5, 1.0, 0.0);
    glTranslatef (3.4, 2.6, -2.9);
    glutWireTetrahedron ();
    glPopMatrix ();

    // Cylinder using Parametric representation
    GLUquadricObj *cylinder;
    glPushMatrix ();
    glTranslatef (-1.0, 1.2, 2.8);
    cylinder = gluNewQuadric ();
    glColor3f (1,0.3, 0.3);
    gluQuadricDrawStyle (cylinder, GLU_LINE);
    gluCylinder (cylinder, 0.6, 0.6, 1.5, 6, 4);
    glPopMatrix ();

    /* Sweep representation of Solids 
     * Hour Glass
     * */
    float d = 1.0;
    float theta = 45.0;

    glPushMatrix ();
    glTranslatef (3.0, 0.0, 0.0);
    for(int phi=0 ;phi < 360 ; phi++) {
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        double x = d*sin(toRad(theta))*cos(toRad(phi));
        double y = d*cos(toRad(theta));
        double z = d*sin(toRad(theta))*sin(toRad(phi));
        glVertex3d(x,y,z);
        glColor3f(0,1,0);
        glVertex3d(-x,-y,-z);      
        glEnd();
    }
    glPopMatrix ();

    glFlush();
    glutSwapBuffers();
}

// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void init() {

  // Set the current clear color to black and the current drawing color to
  // white.
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);

 /* // Set the camera lens to have a 60 degree (vertical) field of view, an
  // aspect ratio of 4/3, and have everything closer than 1 unit to the
  // camera and greater than 40 units distant clipped away.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 4.0/3.0, 1, 40);

  // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
  // <0, 1, 0> pointing upward.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
  */
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


