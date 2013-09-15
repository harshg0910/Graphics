#include <GL/glut.h>
#include <string>
#include <cassert>
#include <iostream>
#include "octree.h"

using namespace std;

// Defines
#define APP_NAME "OctTree"
#define WINDOW_W 600
#define WINDOW_H 600

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;
double zoom              = 1.0;

// Tree symbols specs
const char EMPTY  = '0';
const char FILLED = '1';
const char DIRTY  = '2';

// Constants
const double rotate_step = 5.0;
const double zoom_step   = 0.01;
const double cube_size   = 1.0;
const double center_x    = 0.0;
const double center_y    = 0.0;
const double center_z    = 0.0;


void printAxis(){
    glBegin(GL_LINES);
        glColor3i(1,1,1);
        glVertex3i(0,0,0);
        glVertex3i(1,0,0);     
    glEnd();
    glBegin(GL_LINES);
        glColor3i(0,0,0);
        glVertex3i(0,0,0);
        glVertex3i(0,1,0);     
    glEnd();
    glBegin(GL_LINES);
        glColor3i(0,0,0);
        glVertex3i(0,0,0);
        glVertex3i(0,0,1);     
    glEnd();    
}

void cube(point center,double side,cubeSideColor colors){
    double half_side = side / 2.0;
    double front     = center.z - half_side;
    double back      = center.z + half_side;
    double left      = center.x - half_side;
    double right     = center.x + half_side;
    double bottom    = center.y - half_side;
    double top       = center.y + half_side;

    glPushMatrix();

    // FRONT
    glBegin(GL_POLYGON);
    color col_front = colors.front;
    glColor3f(col_front.red, col_front.green, col_front.blue);
    glVertex3f(right, bottom, front);
    glVertex3f(right, top,    front);
    glVertex3f(left,  top,    front);
    glVertex3f(left,  bottom, front);
    glEnd();

    //
    glBegin(GL_POLYGON);
    color col_back = colors.back;
    glColor3f(col_back.red, col_back.green, col_back.blue);
    glVertex3f(right, bottom, back);
    glVertex3f(right, top,    back);
    glVertex3f(left,  top,    back);
    glVertex3f(left,  bottom, back);
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    color col_right = colors.right;
    glColor3f(col_right.red, col_right.green, col_right.blue);
    glVertex3f(right, bottom, front);
    glVertex3f(right, top,    front);
    glVertex3f(right, top,    back);
    glVertex3f(right, bottom, back);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    color col_left = colors.left;
    glColor3f(col_left.red, col_left.green, col_left.blue);
    glVertex3f(left, bottom, back);
    glVertex3f(left, top,    back);
    glVertex3f(left, top,    front);
    glVertex3f(left, bottom, front);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    color col_top = colors.top;
    glColor3f(col_top.red, col_top.green, col_top.blue);
    glVertex3f(right, top, back);
    glVertex3f(right, top, front);
    glVertex3f(left,  top, front);
    glVertex3f(left,  top, back);
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    color col_bottom = colors.bottom;
    glColor3f(col_bottom.red, col_bottom.green, col_bottom.blue);
    glVertex3f(right, bottom, front);
    glVertex3f(right, bottom, back);
    glVertex3f(left,  bottom, back);
    glVertex3f(left,  bottom, front);
    glEnd();

    glPopMatrix();
    
}

cubeSideColor colors1 = {
    {1.0, 0.5, 0.0},    // Orange
    {0.0,1.0,0.0},      // Green
    {0.0,0.0,1.0},      // Blue
    {1.0,0.0,1.0},      // Magenta
    {1.0,1.0,0.0},      // Yellow
    {1.0,0.0,0.0}       // Red
}; 


point center1 = {
    0.0,    // x
    0.0,    // y
    0.0     // z
};

point center2 = {
    1.0,    //x
    1.0,    //y
    1.0     //z
};

octree* object1 = new octree(center1,colors1,1,true);
octree* object2 = new octree(center2,colors1,1,true);

void makeObjects(){
    // First object
    object1->split();
    octree* c1 = object1->getChild(0);
    c1->split()->getChild(0)->toPrint = false;
    c1->getChild(1)->toPrint = false;
    c1->getChild(4)->toPrint = false;
    c1->getChild(5)->toPrint = false;
    object1->getChild(1)->toPrint = false;
    object1->getChild(6)->toPrint = false;

    //Second object
    object2->split();
    octree* subtree = object2->getChild(0)->split();
    subtree->getChild(0)->toPrint = false;
    subtree->getChild(1)->toPrint = false;
    subtree->getChild(3)->toPrint = false;
    subtree->getChild(4)->toPrint = false;

 subtree = object2->getChild(1)->split();
    subtree->getChild(0)->toPrint = false;
    subtree->getChild(1)->toPrint = false;
    subtree->getChild(2)->toPrint = false;
    subtree->getChild(5)->toPrint = false;

 subtree = object2->getChild(2)->split();
    subtree->getChild(2)->toPrint = false;
    subtree->getChild(1)->toPrint = false;
    subtree->getChild(3)->toPrint = false;
    subtree->getChild(6)->toPrint = false;
 
 subtree = object2->getChild(3)->split();
    subtree->getChild(0)->toPrint = false;
    subtree->getChild(2)->toPrint = false;
    subtree->getChild(3)->toPrint = false;
    subtree->getChild(7)->toPrint = false;

 subtree = object2->getChild(4)->split();
    subtree->getChild(4)->toPrint = false;
    subtree->getChild(5)->toPrint = false;
    subtree->getChild(7)->toPrint = false;
    subtree->getChild(0)->toPrint = false;

 subtree = object2->getChild(5)->split();
    subtree->getChild(4)->toPrint = false;
    subtree->getChild(5)->toPrint = false;
    subtree->getChild(6)->toPrint = false;
    subtree->getChild(1)->toPrint = false;

 subtree = object2->getChild(6)->split();
    subtree->getChild(6)->toPrint = false;
    subtree->getChild(5)->toPrint = false;
    subtree->getChild(7)->toPrint = false;
    subtree->getChild(2)->toPrint = false;
 

 subtree = object2->getChild(7)->split();
    subtree->getChild(4)->toPrint = false;
    subtree->getChild(6)->toPrint = false;
    subtree->getChild(7)->toPrint = false;
    subtree->getChild(3)->toPrint = false;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glScaled(zoom, zoom, zoom);
    printAxis();

    traverse(object1,cube);
    traverse(object2,cube);
    
    glFlush();
    glutSwapBuffers();
}



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

int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_W) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_H) / 2);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow(APP_NAME);

    glEnable(GL_DEPTH_TEST);
    glClearColor (1,1,1,0); // white
    makeObjects();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

