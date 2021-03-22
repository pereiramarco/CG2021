#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Utils/Point3D.h"
#include "../../Utils/Triangle.h"
#include "Group.h"
#include "XMLParser/xmlParser.h"
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

float rotationAngle=1.0f,rotationAngle2=1.0f;
int profundidade=1;
bool axis=false,wire=true,firstCursor=true;
std::unordered_map<std::string,std::vector<Triangle*> > polygons;
std::vector<Group*> groups;
int xMouseB4,yMouseB4;
float yaw=-90.0f,pitch=0; //yaw horizontal turn//pitch vertical turn
Point3D * lookingAtPoint= new Point3D(-2,-2,-2);
Point3D camPosition(2,2,2);

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

void drawFigure(std::string filename,float cr,float cg,float cb) {	
	glBegin(GL_TRIANGLES);
	Triangle * triangle;
	auto& figure = polygons["../models/"+filename];
	for(int i = 0; i < figure.size(); i++) {
		triangle = figure.at(i);
		glColor3f(cr,cg,cb);
		glVertex3f(triangle->ponto1->x,triangle->ponto1->y,triangle->ponto1->z);
		glVertex3f(triangle->ponto2->x,triangle->ponto2->y,triangle->ponto2->z);
		glVertex3f(triangle->ponto3->x,triangle->ponto3->y,triangle->ponto3->z);
	}
	glEnd();
}

void drawFigures(Group *g,int spaceBodyCount) {
	float cr,cg,cb;
	switch(spaceBodyCount) {
		case 0:
			cr=1;cg=1;cb=0;
		break;
		case 1:
			cr=1;cg=0;cb=0;
		break;
		case 2:
			cr=204.0/255;cg=102.0/255;cb=0;
		break;
		case 3:
			cr=0;cg=0;cb=204.0/255;
		break;
		case 4:
			cr=153.0/255;cg=0;cb=0;
		break;
		case 5:
			cr=179/255.0;cg=151/255.0;cb=122/255.0;
		break;
		case 6:
			cr=1;cg=204/255.0;cb=153/255.0;
		break;
		case 7:
			cr=102/255.0;cg=178/255.0;cb=1;
		break;
		case 8:
			cr=0;cg=102/255.0;cb=204/255.0;
		break;
	}
	glPushMatrix();
	for (auto& transform : g->transformations) {
		transform->applyTransform();
	}
	for (auto& modelFileName : g->files) {
		drawFigure(modelFileName,cr,cg,cb);
	}
	for (auto& group : g->nestedGroups) {
		drawFigures(group,spaceBodyCount);
	}
	glPopMatrix();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camPosition.x,camPosition.y,camPosition.z, 
		      lookingAtPoint->x+camPosition.x,lookingAtPoint->y+camPosition.y,lookingAtPoint->z+camPosition.z,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here
	glRotatef(rotationAngle,0.0,1.0,0.0);
    glRotatef(rotationAngle2,1.0,0.0,1.0);

// put drawing instructions here
	if (axis) meteAxis();
	int i=0;
	for (auto& g : groups) {
		drawFigures(g,i++);
	}

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
	Point3D look = lookingAtPoint->clone();
	Point3D ylook(-look.z,0,look.x);
	float speed=0.1f;
	switch(key) {
		case 'w':
			camPosition+=look*speed;
			break;
		case 'a':
			camPosition-=ylook*speed;
			break;	
		case 's':
			camPosition-=look*speed;
			break;
		case 'd':
			camPosition+=ylook*speed;
			break;
		case ' ':
			axis=!axis;
			break;
		case 'p':
			glPolygonMode( GL_FRONT_AND_BACK, wire?GL_LINE:GL_FILL );
			wire=!wire;
			break;
		default:
            break;
	}
}

double radians(double degree)
{
    return (degree * (M_PI / 180));
}

void mouseControls(int x,int y) {

	if (firstCursor)
    {
        xMouseB4 = x;
        yMouseB4 = y;
        firstCursor = false;
    }

	float xoffset = x - xMouseB4;
	float yoffset = yMouseB4 - y; // reversed since y-coordinates range from bottom to top
	xMouseB4=x;
	yMouseB4=y;

	const float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw+=xoffset;
	pitch+=yoffset;
	
	if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    lookingAtPoint->x = cosf(radians(yaw)) * cosf(radians(pitch));
    lookingAtPoint->y = sinf(radians(pitch));
    lookingAtPoint->z = sinf(radians(yaw)) * cosf(radians(pitch));
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
		float redValue=(1.0*rand())/RAND_MAX;
		float greenValue=(1.0*rand())/RAND_MAX;
		float blueValue=(1.0*rand())/RAND_MAX;
		triangle = new Triangle(vertices.at(indicePonto1),vertices.at(indicePonto2),vertices.at(indicePonto3),redValue,greenValue,blueValue);
		triangles.push_back(triangle);
	}
	polygons[filename] = triangles;
}

void readConfig(int argc, char **argv) {
	std::string name;
	xmlContent * parser;
	if(argc == 2) {
		name = "../configs/" + std::string(argv[1]);
		parser = new xmlContent(name);
	}
	else {
		parser = new xmlContent();
	}
	groups=parser->parse();
	std::unordered_set<std::string> files = parser->getModels(); //é um set para evitar repetidos
	for(auto& filename : files) {
		std::string model = "../models/" + filename;
		readFile3D(model);
	}
}

int main(int argc, char **argv) {
	readConfig(argc,argv);
	
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
	glutPassiveMotionFunc(mouseControls);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	return 1;
}