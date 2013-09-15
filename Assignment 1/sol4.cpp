#include "vertexList.h"

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;

void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
 
  //  Request display update
  glutPostRedisplay();
 
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float cuboid1[][3] = 
        {
            {  0.5,  0.25,  0.25},
            {  0.5,  0.25, -0.25},
            {  0.5, -0.25, -0.25},
            {  0.5, -0.25,  0.25},
            { -0.5,  0.25,  0.25},
            { -0.5,  0.25, -0.25},
            { -0.5, -0.25, -0.25},
            { -0.5, -0.25,  0.25}
        }; 

    float cuboid2[][3] = 
        {
            {  0.25,  0.5,  0.25},
            {  0.25,  0.5, -0.25},
            { -0.25,  0.5, -0.25},
            { -0.25,  0.5,  0.25},
            {  0.25, -0.5,  0.25},
            {  0.25, -0.5, -0.25},
            { -0.25, -0.5, -0.25},
            { -0.25, -0.5,  0.25}
        };

    float cuboid3[][3] = 
        {
            {  0.25,  0.25,  0.5},
            {  0.25, -0.25,  0.5},
            { -0.25, -0.25,  0.5},
            { -0.25,  0.25,  0.5},
            {  0.25,  0.25, -0.5},
            {  0.25, -0.25, -0.5},
            { -0.25, -0.25, -0.5},
            { -0.25,  0.25, -0.5}
        };

    vector<Point3D> cubeVertices1 (&cuboid1[0], &cuboid1[0]+8);
    vector<Point3D> cubeVertices2 (&cuboid2[0], &cuboid2[0]+8);
    vector<Point3D> cubeVertices3 (&cuboid3[0], &cuboid3[0]+8);
    float color[3] = {1.0, 0.5, 0.2};
    glRotatef (rotate_x, 1.0, 0.0, 0.0);
    glRotatef (rotate_y, 0.0, 1.0, 0.0);

    // TODO More objects in vertexList representation
    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    drawObjectGivenVertices (CHULL_AND_TRIANGULATE, cubeVertices1, color);
    drawObjectGivenVertices (CHULL_AND_TRIANGULATE, cubeVertices2, color);
    drawObjectGivenVertices (CHULL_AND_TRIANGULATE, cubeVertices3, color);

  glFlush();
  glutSwapBuffers();
}

int main(int argc, char* argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Create window
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Awesome Mesh");
 
  glEnable(GL_DEPTH_TEST);
 
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 
  glutMainLoop();
 
  return 0;
}
