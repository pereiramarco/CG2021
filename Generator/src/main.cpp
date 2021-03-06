#include <string>
#include <math.h>
#include <iostream>
#include "../include/Sphere.h"
#include "../include/Cone.h"
#include "../include/Box.h"
#include "../include/Plane.h"
#include "../include/Model.h"


using namespace std;
/*
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

    Sphere *s = new Sphere(1,10,10);
    s->generate();
	s->saveToFile("sphere.3d");

    Cone *c = new Cone(1,2,10,10);
    c->generate();
    c->saveToFile("cone.3d");

    Box *b= new Box(5,5,5,4);
    b->generate();
    b->saveToFile("box.3d");
    
    
    Plane *p = new Plane(10,10);
    p->generate();
    p->saveToFile("plane.3d");



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
*/

int main(int argc, char **argv) {
	string filename;
	Model* m;
    if (argc>2) {
        string type=string(argv[1]);
        if (type=="sphere") {
            if (argc!=6) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int radius=atoi(argv[2]),slices=atoi(argv[3]),stacks=atoi(argv[4]);
            Sphere *s = new Sphere(radius,slices,stacks);
            m=s->generate();
            filename=string(argv[5]);
        }
        else if (type=="cone") {
            if (argc!=7) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int radiusBase=atoi(argv[2]), height=atoi(argv[3]),slices=atoi(argv[4]),stacks=atoi(argv[5]);
            Cone *c = new Cone(radiusBase,height,slices,stacks);
            m=c->generate();
            filename=string(argv[6]);
        }
        else if (type=="box") {
            if (argc!=6 && argc!=7) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int width=atoi(argv[2]),depth=atoi(argv[3]),height=atoi(argv[4]);
            Box *b = new Box(width,depth,height,argc==6?0:atoi(argv[5]));
            m=b->generate();
            filename=string(argv[argc==6?5:6]);
        }
        else if (type=="plane") {
            if (argc!=5) {
                cout<< "Not enough arguments\n";
                return 1;
            }
            int width=atoi(argv[2]),depth=atoi(argv[3]);
            Plane *p = new Plane(width,depth);
            m=p->generate();
            filename=string(argv[4]);
        }
		else return 1;
        m->saveToFile(filename);
    }
}
