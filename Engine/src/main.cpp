#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Utils/Ponto3D.h"
#include "../../Utils/Triangulo.h"
#include "XMLParser/xmlParser.h"
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

float rotateSpeed=1.0f,rotateSpeed2=1.0f;
int profundidade=1;
bool axis=false;
std::unordered_map<std::string,std::vector<Triangulo*> > polygons;

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

void drawFigures() {
	Triangulo * triangulo;
	for(auto value : polygons) {
		for(int i = 0; i < value.second.size(); i++) {
			triangulo = value.second.at(i);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f,1.0f,1.0f);
			glVertex3f(triangulo->ponto1->x,triangulo->ponto1->y,triangulo->ponto1->z);
    		glVertex3f(triangulo->ponto2->x,triangulo->ponto2->y,triangulo->ponto2->z);
    		glVertex3f(triangulo->ponto3->x,triangulo->ponto3->y,triangulo->ponto3->z);
			glEnd();
		}
	}
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

	drawFigures();

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

void readFile3D(std::string filename) {
	std::ifstream fp(filename);
	int numVertexes, numTriangles;
	float x,y,z;
	std::string line;
	std::getline(fp,line);
	std::istringstream iss(line);
	iss >> numVertexes >> numTriangles;
	int i;
	std::vector<Ponto3D*> vertices;
	std::vector<Triangulo*> triangulos;
	Triangulo * triangulo;
	for(i = 0; i < numVertexes; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> x >> y >> z)) {
			std::cout << "Erro! \n";
			break;
		}
		Ponto3D * ponto = new Ponto3D(x,y,z);
		vertices.push_back(ponto);
	}
	for(i = 0; i < numTriangles; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> x >> y >> z)) {
			std::cout << "Erro! \n";
			break;
		}
		triangulo = new Triangulo(vertices.at(x),vertices.at(y),vertices.at(z));
		triangulos.push_back(triangulo);
	}
	polygons[filename] = triangulos;
}

int main(int argc, char **argv) {
	xmlContent parser;
	parser.parse();
	//readFile3D("../sphere.3d");
	readFile3D("../plane.3d");
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