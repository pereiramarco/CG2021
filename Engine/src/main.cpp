#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Utils/Point3D.h"
#include "../../Utils/Triangle.h"
#include "XMLParser/xmlParser.h"
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstdlib>

using namespace std;

float rotationAngle=1.0f,rotationAngle2=1.0f;
int profundidade=1;
bool axis=false;
std::unordered_map<std::string,std::vector<Triangle*> > polygons;

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
	Triangle * triangle;
	for(auto value : polygons) {
		for(int i = 0; i < value.second.size(); i++) {
			triangle = value.second.at(i);
			glBegin(GL_TRIANGLES);
			glColor3f(triangle->redValue,triangle->greenValue,triangle->blueValue);
			glVertex3f(triangle->ponto1->x,triangle->ponto1->y,triangle->ponto1->z);
    		glVertex3f(triangle->ponto2->x,triangle->ponto2->y,triangle->ponto2->z);
    		glVertex3f(triangle->ponto3->x,triangle->ponto3->y,triangle->ponto3->z);
			glEnd();
		}
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(profundidade*2,profundidade*2,profundidade*2, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
	glRotatef(rotationAngle,0.0,1.0,0.0);
    glRotatef(rotationAngle2,1.0,0.0,1.0);

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
		case 'd':
			rotationAngle+=10;
			break;
		case 'a':
			rotationAngle-=10;
			break;
		case 's':
			profundidade+=1;
			break;
		case 'w':
			profundidade=profundidade==1?1:profundidade-1;
			break;
		case ' ':
			axis=!axis;
			break;
		default:
            break;
	}
}


void mouseControls(int x,int y) {
	rotationAngle=x/2%360;
    rotationAngle2=y/2%360;
}

void readFile3D(std::string filename) {
	srand(time(NULL)); //dá seed à aleatoriedade de forma a ter sempre cores diferentes.
	std::ifstream fp(filename);
	int numVertexes, numTriangles;
	float x,y,z;
	std::string line;
	std::getline(fp,line);
	std::istringstream iss(line);
	iss >> numVertexes >> numTriangles;
	int i;
	std::vector<Point3D*> vertices;
	std::vector<Triangle*> triangles;
	Triangle * triangle;
	// Aquisição dos Pontos de Desenho dos Triangles do ficheiro
	for(i = 0; i < numVertexes; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> x >> y >> z)) {
			std::cout << "Erro! \n";
			break;
		}
		Point3D * ponto = new Point3D(x,y,z);
		vertices.push_back(ponto);
	}
	// Aquisição dos Triangles a partir de 3 Pontos do Ficheiro
	int indicePonto1, indicePonto2, indicePonto3;
	for(i = 0; i < numTriangles; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> indicePonto1 >> indicePonto2 >> indicePonto3)) {
			std::cout << "Erro! \n";
			break;
		}
		float redValue=(1.0*rand())/INT_MAX;
		float greenValue=(1.0*rand())/INT_MAX;
		float blueValue=(1.0*rand())/INT_MAX;
		triangle = new Triangle(vertices.at(indicePonto1),vertices.at(indicePonto2),vertices.at(indicePonto3),redValue,greenValue,blueValue);
		triangles.push_back(triangle);
	}
	polygons[filename] = triangles;
}

int main(int argc, char **argv) {
	xmlContent parser;
	parser.parse();
	std::vector<std::string> files = parser.getModels();
	for(int i = 0; i < files.size();i++) {
		std::string model = "../" + files[i];
		readFile3D(model);
	}
	
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG2021 Dream Team");
		
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