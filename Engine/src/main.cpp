#ifdef __MAIN__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <math.h>

using namespace std;

float rotateSpeed=1.0f,rotateSpeed2=1.0f;
int profundidade=1;
bool axis=false;

void meteAxis() {
	glBegin(GL_LINES);
	
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f,  100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f,  100.0f);
	
	glEnd();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(profundidade,profundidade,profundidade, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
	glRotatef(rotateSpeed,0.0,1.0,0.0);
    glRotatef(rotateSpeed2,1.0,0.0,1.0);

// put drawing instructions here
	if (axis) meteAxis();
	glBegin(GL_TRIANGLES);


    glEnd();

	// End of frame
	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// write function to process keyboard events
void keyboardInput(unsigned char key, int x, int y) {
	switch(key) {
		case 'w':
			rotateSpeed+=10;
			break;
		case 's':
			rotateSpeed-=10;
			break;
		case 'm':
			profundidade+=1;
			break;
		case 'n':
			profundidade=profundidade==1?1:profundidade-1;
			break;
		case ' ':
			axis=!axis;
			break;
		default:
            break;
	}
	glutPostRedisplay(); 
}


void mouseControls(int x,int y) {
	rotateSpeed=x%360;
    rotateSpeed2=y%360;
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardInput);
	glutMotionFunc(mouseControls);
	glutPassiveMotionFunc(mouseControls);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}