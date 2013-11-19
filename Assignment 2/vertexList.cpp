#include "vertexList.h"


void drawTriangles (vector<Point3D> vertices, float color[3]) {
    // Represent the cube
    glPushMatrix ();
    glBegin (GL_TRIANGLES); 
    glColor3f (color[0], color[1], color[2]); // green

    // Front-face 0->1->2->3
    for (uint i=0; i<vertices.size (); i++) {
        cout << vertices[i][0] << " " << vertices[i][1] << " " <<vertices[i][2] << endl;
        glVertex3fv (vertices[i]);
    }

    glEnd ();
    glPopMatrix ();
    glFlush ();
}

void drawTrianglurMeshes (vector<Point3D> vertices, float color[3]) {
    // Represent the cube
    glPushMatrix ();
    glBegin (GL_TRIANGLE_STRIP); 
    glColor3f (color[0], color[1], color[2]); // green

    // Front-face 0->1->2->3
    for (uint i=0; i<vertices.size (); i++) {
        cout << vertices[i][0] << " " << vertices[i][1] << " " <<vertices[i][2] << endl;
        glVertex3fv (vertices[i]);
    }

    glEnd ();
    glPopMatrix ();
    glFlush ();
}
/*****************************/

#define pb push_back
#define mp make_pair
#define sz(a) (int)(a).size()
#define forn(i,n) for (int i=0; i<int(n); ++i)
typedef pair<int,int> ii;

float det_d(vector<float> mat, int d) {
    if( d == 1) return mat[0];
    float total = 0;
    forn(j, d) {
        float mul;
        if(j%2) mul = -mat[j];
        else mul = mat[j];
        
        vector<float> mat1(mat.begin()+d, mat.end());
        forn(i, d-1) {
            //cout << i+1 << " " << j << " " << d<< endl;
            mat1.erase(mat1.begin() + (d-i-2)*d+j);
        }
        total += mul*det_d(mat1, d-1);
    }
    return total;
}

vector<pair<int, ii> > triangulate_convex(vector<pair<float, pair<float, float> > > &v) {
    vector<pair<int, ii> > ans;
    forn(i, sz(v)) {
        forn(j, sz(v)) {
            if( j <= i ) continue;
            forn(k, sz(v)) {
                if(k <= i || k <= j) continue;
                // checking for the plane (made with ith, jth and kth point) , with all the other points.
                vector<int> dets;
                forn(l, sz(v)) {
                    if(i==l || j==l || k==l) continue;
                    vector<float> mat;
                    mat.pb(v[i].first);
                    mat.pb(v[i].second.first);
                    mat.pb(v[i].second.second);
                    mat.pb(1);

                    mat.pb(v[j].first);
                    mat.pb(v[j].second.first);
                    mat.pb(v[j].second.second);
                    mat.pb(1);
                
                    mat.pb(v[k].first);
                    mat.pb(v[k].second.first);
                    mat.pb(v[k].second.second);
                    mat.pb(1);
                
                    mat.pb(v[l].first);
                    mat.pb(v[l].second.first);
                    mat.pb(v[l].second.second);
                    mat.pb(1);
                    int x = det_d(mat, 4);
                    if(x != 0.0)
                    dets.pb(x);
                }
                bool yes = true;
                if(dets.size() > 0) {
                    forn(q, sz(dets)) {
                        if(dets[0]*dets[q] < 0) {
                            yes = false;
                            break;
                        }
                    }
                }
                if(yes) ans.pb(mp(i, mp(j,k)));
            }
        }
    }
    return ans;
}

// display() Callback function
// ----------------------------------------------------------
void createConvexHullAndTriangulate (vector<Point3D> vertices) {
 
  vector<pair<float, pair<float, float> > > v;
  
  for (size_t i=0; i<vertices.size (); i++) 
      v.pb (mp (vertices[i][0], mp (vertices[i][1], vertices[i][2])));

    vector<pair<int, ii > >ans = triangulate_convex(v);
    glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    glBegin (GL_POLYGON);

    forn(i, sz(ans)) {
    int x=ans[i].first, y=ans[i].second.first, z=ans[i].second.second;
            glColor3f(1, 0, 0); glVertex3f(v[x].first, v[x].second.first, v[x].second.second);
            glColor3f(1, 0, 0); glVertex3f(v[y].first, v[y].second.first, v[y].second.second);
            glColor3f(0, 1, 0); glVertex3f(v[z].first, v[z].second.first, v[z].second.second);
    }

    glEnd();
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
}


/*****************************/

typedef struct pt {
    float x;
    float y;
    float z;
} pt;

vector<pt> triangleMesh;
vector<int> indicesMesh;

void createVertices (pt p1, pt p2, pt p3) {
    int division = 5;

    if (triangleMesh.size () > 0) {
        triangleMesh.clear ();
        indicesMesh.clear ();
    }

    triangleMesh.push_back (p1);
    for (int i=1; i<=division; i++) {
        pt pl, pr;
        pl.x = ( p1.x * (division - i) + p2.x * i ) / division;
        pl.y = ( p1.y * (division - i) + p2.y * i ) / division;
        pl.z = ( p1.z * (division - i) + p2.z * i ) / division;
        pr.x = ( p1.x * (division - i) + p3.x * i ) / division;
        pr.y = ( p1.y * (division - i) + p3.y * i ) / division;
        pr.z = ( p1.z * (division - i) + p3.z * i ) / division;

        triangleMesh.push_back (pl);
        for (int j=1; j<i; j++) {
            pt p;
            p.x = ( pl.x * (i-j) + pr.x * j ) / i;
            p.y = ( pl.y * (i-j) + pr.y * j ) / i;
            p.z = ( pl.z * (i-j) + pr.z * j ) / i;
            triangleMesh.push_back (p);
        }

        triangleMesh.push_back (pr);
    }

    int prev = 0, cur = 1;
    for (int i=1; i<=division; i++) {
        indicesMesh.push_back (prev);
        indicesMesh.push_back (cur);
        indicesMesh.push_back (cur+1);

        for (int j=prev, k=cur+1; j<cur-1; j++, k++) {
            indicesMesh.push_back (j);
            indicesMesh.push_back (j+1);
            indicesMesh.push_back (k);

            indicesMesh.push_back (j+1);
            indicesMesh.push_back (k);
            indicesMesh.push_back (k+1);
        }

        prev = cur;
        cur += i+1;
    }
}

// display() Callback function
// ----------------------------------------------------------
void triangularMeshes (vector<Point3D> vertices ) {
 
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // Reset transformations
  glLoadIdentity();
 
  if (vertices.size () < 3) return;

  int i=0;
//  for (int i=0; i<vertices.size ()-2; i++) {
      pt p1 = {vertices[i][0],vertices[i][1],vertices[i][2]}; 
      pt p2 = {vertices[i+1][0],vertices[i+1][1],vertices[i+1][2]}; 
      pt p3 = {vertices[i+2][0],vertices[i+2][1],vertices[i+2][2]}; 
      createVertices (p1,p2,p3);
      glEnableClientState( GL_VERTEX_ARRAY );
      glColor3f(1.0f, 0.0f, 0.0f); // red
      glVertexPointer ( 3, GL_FLOAT, 0, &triangleMesh[0] );
      glDrawElements( GL_TRIANGLES, indicesMesh.size (), GL_UNSIGNED_INT, &indicesMesh[0] );
      glDisableClientState( GL_VERTEX_ARRAY ); 

      cout << "size of vA" << triangleMesh.size () << endl;
      cout << "size of iA" << indicesMesh.size () << endl;

      glFlush();
      glutSwapBuffers();
 // }

}

/****************************/
void drawPolygons (vector<Point3D> vertices, float color[3]) {
     // add polygons here
    // Represent the cube
    glPushMatrix ();

 //   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//    glBegin (GL_POLYGON); 
    glBegin (GL_TRIANGLE_FAN); 
    glColor3f (color[0], color[1], color[2]); // green

    // Front-face 0->1->2->3
    for (uint i=0; i<vertices.size (); i++) 
        glVertex3fv (vertices[i]);

    glEnd ();
 //   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glPopMatrix ();
    glFlush ();
}

/*
 * 0->1->2->3 FRONT FACE
 * 4->5->6->7 BACK FACE
 * 0->1->4->5 TOP
 * 3->2->6->7 BOTTOM
 * 0->3->4->7 LEFT
 * 1->2->6->5 RIGHT
 * */
void drawCube (vector<Point3D> vertices, float color[3]) {
    if (vertices.size () < CUBE_VERTICES) {
        cerr << "Vertices required to represent a cube is " << CUBE_VERTICES << endl;
        return;
    }

    // Represent the cube
    glPushMatrix ();

    glBegin (GL_QUADS); 
    // glColor3f (color[0], color[1], color[2]); // green

    glColor3f(0.0f, 1.0f, 0.0f); // green
    // Front-face 0->1->2->3
    for (int i=0; i<4; i++)
        glVertex3fv (vertices[i]);

    glColor3f(1.0f, 0.5f, 0.0f); // orange
    // Back-face 4->5->6->7
    for (int i=4; i<8; i++)
        glVertex3fv (vertices[i]);

    glColor3f(1.0f, 0.0f, 0.0f); // red
    // Top-face 0->1->4->5 
    glVertex3fv (vertices[0]); glVertex3fv (vertices[1]);
    glVertex3fv (vertices[5]); glVertex3fv (vertices[4]);

    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    // Bottom-face 3->2->6->7
    glVertex3fv (vertices[3]); glVertex3fv (vertices[2]);
    glVertex3fv (vertices[6]); glVertex3fv (vertices[7]);

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    // Left-face 0->3->7->4
    glVertex3fv (vertices[0]); glVertex3fv (vertices[3]);
    glVertex3fv (vertices[7]); glVertex3fv (vertices[4]);

    glColor3f(1.0f, 0.0f, 1.0f); // magenta
    // Right-face 1->2->6->5 
    glVertex3fv (vertices[1]); glVertex3fv (vertices[2]);
    glVertex3fv (vertices[6]); glVertex3fv (vertices[5]);
    glEnd ();  

    glPopMatrix ();
    glFlush ();
}

void drawObjectGivenVertices (enum TypeOfObject typeOfObject, vector<Point3D> vertices, float color[3]) {
    switch ( typeOfObject ) {
        case CUBE:
            drawCube (vertices, color);
            break;
        case TRIANGULAR_MESHES:
            drawTrianglurMeshes (vertices, color);
            break;
        case TRIANGLE:
            drawTriangles (vertices, color);
            break;
        case POLYGON:
            drawPolygons (vertices, color);
            break;
        case TRIANGLE_MESH:
            triangularMeshes (vertices);
            break;
        case CHULL_AND_TRIANGULATE:
            createConvexHullAndTriangulate (vertices);
            break;
        default:
            cerr << "OBJECT NOT SUPPORTED" << endl;
    }
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
void glutMainDefault (int argc, char** argv, string programName, displayFunc display, keyControl keyboard,int iWS[2], int iWP[2]) {
  glutInit (&argc, argv);
  glutInitWindowSize (iWS[0], iWS[1]);
  glutInitWindowPosition (iWP[0], iWP[1]);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow (programName.c_str ());

  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  //glutInitDefault ();
  glutMainLoop ();
}

// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void glutInitDefault() {
  // Set the current clear color to black and the current drawing color to
  // white.
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);

  // Set the camera lens to have a 60 degree (vertical) field of view, an
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
}


