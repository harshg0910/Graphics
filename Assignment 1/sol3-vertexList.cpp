#include "vertexList.h"

// Default Main Function implementation for OpenGL programs
int iWindowSize[2] = {800, 600};
int iWindowPosition[2] = {80, 80};

// Global Variables
double rotate_y          = 0.0;
double rotate_x          = 0.0;
double zoom              = 1.0;

// Constants
const double rotate_step = 5.0;
const double zoom_step   = 0.01;
const double cube_size   = 1.0;
const double center_x    = 0.0;
const double center_y    = 0.0;
const double center_z    = 0.0;

void keyboard(unsigned char key, int x, int y) {
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

void renderFirstObject(){
    float cuboid1[][3] = 
        {
            {0.5, 0.5,0.5},
            {0.5, 0.0,0.5},
            {0.0, 0.0,0.5},
            {0.0, 0.5,0.5},
            {0.5, 0.5,-0.5},
            {0.5, 0.0,-0.5},
            {0.0, 0.0,-0.5},
            {0.0, 0.5,-0.5}
        };

    float cuboid2[][3] = 
        {
                       
            {0.0,0.0 ,0.5},
            {0.0,-0.5,0.5},
            {-0.5,-0.5,0.5},
            {-0.5,0.0 ,0.5},

            {0.0,0.0 ,-0.5},
            {0.0 ,-0.5, -0.5},
            {-0.5,-0.5, -0.5},
            {-0.5,0.0 ,-0.5}

        };

    float cuboid3[][3] = 
        {
            {0.0  ,0.5 ,0.5},
            {0.0  ,0.0 ,0.5},
            {-0.5  ,0.0 ,0.5},
            {-0.5  ,0.5 ,0.5},
            
            {0.0  , 0.5, 0.0},
            {0.0 , 0.0, 0.0},
            {-0.5 , 0.0, 0.0},
            {-0.5 , 0.5, 0.0}


        };

    float cuboid4[][3] = 
    {
        
        {0.25  ,0.0 ,0.5},
        {0.25  ,-0.5 ,0.5},
        {0.0  ,-0.5 ,0.5},
        {0.0  ,0.0 ,0.5},

        {0.25 , 0.0, 0.0},
        {0.25 , -0.5, 0.0},
        {0.0  , -0.5, 0.0},
        {0.0 , 0.0, 0.0}
        

    };

    vector<Point3D> cubeVertices1 (&cuboid1[0], &cuboid1[0]+8);
    vector<Point3D> cubeVertices2 (&cuboid2[0], &cuboid2[0]+8);
    vector<Point3D> cubeVertices3 (&cuboid3[0], &cuboid3[0]+8);
    vector<Point3D> cubeVertices4 (&cuboid4[0], &cuboid4[0]+8);
    float color[3] = {1.0, 0.5, 0.2};

    // TODO More objects in vertexList representation
    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    drawObjectGivenVertices (CUBE, cubeVertices1, color);
    drawObjectGivenVertices (CUBE, cubeVertices2, color);
    drawObjectGivenVertices (CUBE, cubeVertices3, color);
    drawObjectGivenVertices (CUBE, cubeVertices4, color);
}

void renderSecondObject(){
    double x_cent = 1.0;
    double y_cent = 1.0;
    double z_cent = 1.0;

     float cuboid1[][3] = 
        {
            {x_cent+0.5,y_cent+0.25,z_cent+0.25},
            {x_cent+0.5,y_cent+0.25,z_cent-0.25},
            {x_cent+0.5,y_cent-0.25,z_cent-0.25},
            {x_cent+0.5,y_cent-0.25,z_cent+0.25},
            {x_cent-0.5,y_cent+0.25,z_cent+0.25},
            {x_cent-0.5,y_cent+0.25,z_cent-0.25},
            {x_cent-0.5,y_cent-0.25,z_cent-0.25},
            {x_cent-0.5,y_cent-0.25,z_cent+0.25}
        };

    float cuboid2[][3] = 
        {
            {x_cent+0.25,y_cent+0.5,z_cent+ 0.25},
            {x_cent+0.25,y_cent+0.5,z_cent-0.25},
            {x_cent-0.25, y_cent+0.5,z_cent-0.25},
            {x_cent-0.25, y_cent+0.5,z_cent+ 0.25},
            {x_cent+0.25,y_cent-0.5,z_cent+ 0.25},
            {x_cent+0.25,y_cent-0.5,z_cent-0.25},
            {x_cent-0.25, y_cent-0.5,z_cent-0.25},
            {x_cent-0.25, y_cent-0.5,z_cent+ 0.25}
        };

    float cuboid3[][3] = 
        {
            {x_cent+0.25,y_cent+0.25,z_cent+0.5},
            {x_cent+0.25,y_cent-0.25,z_cent+0.5},
            {x_cent-0.25, y_cent-0.25,z_cent+0.5},
            {x_cent-0.25, y_cent+0.25,z_cent+0.5},
            {x_cent+0.25,y_cent+0.25,z_cent-0.5},
            {x_cent+0.25,y_cent-0.25,z_cent-0.5},
            {x_cent-0.25, y_cent-0.25,z_cent-0.5},
            {x_cent-0.25, y_cent+0.25,z_cent-0.5}
        };
    vector<Point3D> cubeVertices1 (&cuboid1[0], &cuboid1[0]+8);
    vector<Point3D> cubeVertices2 (&cuboid2[0], &cuboid2[0]+8);
    vector<Point3D> cubeVertices3 (&cuboid3[0], &cuboid3[0]+8);
    float color[3] = {1.0, 0.5, 0.2};

    // TODO More objects in vertexList representation
    // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
    // axes are ten units long.
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    drawObjectGivenVertices (CUBE, cubeVertices1, color);
    drawObjectGivenVertices (CUBE, cubeVertices2, color);
    drawObjectGivenVertices (CUBE, cubeVertices3, color);
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glScaled(zoom, zoom, zoom);
    
    renderSecondObject();
    renderFirstObject();
    
//    drawObjectGivenVertices (TRIANGLE, cubeVertices, color);
    glFlush();
    glutSwapBuffers();
}

int main (int argc, char **argv) {
  glutMainDefault (argc, argv, "Vertex List", display, keyboard, iWindowSize, iWindowPosition);

    return 0;
}

