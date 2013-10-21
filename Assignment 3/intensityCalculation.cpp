#include "intensityCalculation.h"
#include <GL/glut.h>

#define toRad(a) a*3.14/180
typedef point vector3;
Intensity intensityAtP (Intensity Ia, vector<Intensity> Is, vector<point> Ls, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pN, point pV, double ns) {
	// Ambient component
	Intensity I = Ia;
	I.intensityMulK (Ka);

	for(int i=0; i<Ls.size(); ++i) 
		I = I + intensityAtP (Is[i], Ka, Kd, Ks, pP, Ls[i], pN, pV, ns);

	return I;
}

Intensity intensityAtP (Intensity Il, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pL, point pN, point pV, double ns) {
	Intensity I;
	// Diffuse Component
	vector3 N(pN);
	N.normalize();

	pL = pL-pP;
	vector3 L(pL);
	L.normalize();

	double cosT = N.dot(L);
	if (cosT > 0.0) {
		Intensity Id = Il;
		Id.intensityMulK (Kd);

		SurfaceK kCosT (cosT, cosT, cosT);
		Id.intensityMulK (kCosT);

		I = I + Id;

		// Specular Diffusion
		pV = pV-pP;
		vector3 V(pV);
		pV.normalize();

		N.scale (2*cosT);
		vector3 R(N);
		R = R-L;

		double cosPhi = V.dot(R);
		if (cosPhi > 0.0) {
			Intensity Is = Il;
			Is.intensityMulK (Kd);

			cosPhi = pow(cosPhi, ns);
			SurfaceK kCosPhi (cosPhi, cosPhi, cosPhi);
			Is.intensityMulK (kCosPhi);

			I = I + Is;
		}
	}

	return I;
}

// World to Eye coordinates 
void worldToEye (vector3 eye, vector3 coi, vector3 v_up) {
	vector3 n = eye-coi;
	n.normalize();

	vector3 u = v_up.cross (n);
	u.normalize();

	vector3 v = n.cross (u);

	GLfloat edu = eye.x*u.x + eye.y*u.y +  eye.z*u.z;
	GLfloat edv = eye.x*v.x + eye.y*v.y +  eye.z*v.z;
	GLfloat edn = eye.x*n.x + eye.y*n.y +  eye.z*n.z;

	GLfloat w2e[16] = 
	{
		u.x, v.x, u.z, 0 ,
		u.y, v.y, v.z, 0 ,
		u.z, v.z, n.z, 0 ,
		-edu,-edv,-edn, 1 
	};

	glMultMatrixf (w2e);
} 

// Set the camera to this position with respective parameters
void setPerspective (GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
	fovy = toRad (fovy);
	fovy /= 2;
	GLfloat f = cos(fovy) / sin(fovy);

	GLfloat persepectiveMat[16] = 
	{
		f/aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (zFar+zNear)/(zNear-zFar), -1,
		0, 0,(2*zFar*zNear)/(zNear-zFar),0
	};

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMultMatrixf (persepectiveMat);
	glMatrixMode (GL_MODELVIEW);
}

// Convert the window to view port
void setViewPort (GLint vx1, GLint vx2, GLint vy1, GLint vy2,
		GLint wx1, GLint wx2, GLint wy1, GLint wy2) {
	GLfloat sx = (vx2-vx1) / (wx2-wx1);
	GLfloat sy = (vy2-vy1) / (wy2-wy1);
	GLfloat tx = sx * (-wx1) + vx1;
	GLfloat ty = sy * (-wy1) + vy1;

	/*Matri4x4 viewMatrix = 
	  {
	  sx,  0, 0, tx,
	  0, sy, 0, ty,
	  0,  0, 0,  0,
	  0,  0, 0,  1
	  }; */

	GLfloat viewMatrix[16] = 
	{
		sx,  0, 0,  0,
		0, sy, 0,  0,
		0,  0, 0,  0,
		tx, ty, 0,  1
	};


	glMultMatrixf (viewMatrix);
}


// Global Variables
#define TRUE 1
#define FALSE 0
#define VIEWING_DISTANCE_MIN  3.0

static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

point eye(0, 0, -g_fViewDistance), coi(0, 0, 1), v_up(1, 0, 0);

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

	GLfloat clrs[4];
	glGetLightfv (GL_LIGHT0, GL_AMBIENT, clrs);

	cout << "ambient light is: " << " R=" << clrs[0] << ", G=" << clrs[1] << ", B=" << clrs[2] << ", A=" << clrs[3] << endl;

	glMatrixMode(GL_MODELVIEW);

	// Main object (cube) ... transform to its coordinates, and render
	glPushMatrix();
	glRotatef(15, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(g_fTeapotAngle, 0, 0, 1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone); 
	glColor4fv(colorBlue);
	DrawCube (1.0);
	glPopMatrix();

	// Child object (teapot) ... relative transform, and render
	glPushMatrix();
	glTranslatef(5, 0, 0);
	glRotatef(g_fTeapotAngle2, 1, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
	//glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	//glColor4fv(colorBronzeDiff);
	glutSolidTeapot(0.5); 
	glPopMatrix(); 

}

void display(void) {
	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();

	//gluLookAt(2, 3, -g_fViewDistance, 5, 4,10, 0, 1, 0);
	//point eye(2, 3, -g_fViewDistance), coi(5, 4, 10), v_up(0, 1, 0);
	worldToEye(eye, coi, v_up);

	// Set up the stationary light
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

	// Render the scene
	RenderObjects();

	// Make sure changes appear onscreen
	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(45, (float)g_Width*2 / g_Height, g_nearPlane, g_farPlane/10);
	setPerspective (65, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
	glMatrixMode(GL_MODELVIEW);
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


