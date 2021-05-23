#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../Utils/Point3D.h"
#include "../include/Group.h"
#include "../include/VBO.h"
#include "../include/Lights/Light.h"
#include "../include/XMLParser/xmlParser.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <memory>

bool Translation::showCurves=false;
bool Transform::paused=false;
float Transform::time_multiplier=1;
int Transform::retroceder=1;
bool axis=false,wire=true,firstCursor=true;
std::unordered_map<std::string,VBO> buffers;
std::vector<Group> groups;
std::vector<std::shared_ptr<Light>> lights;
int xMouseB4,yMouseB4;
float yaw=-155.0f,pitch=0.0f; //yaw horizontal turn//pitch vertical turn
float sensitivity = 0.3f; //sensibilidade do rato
float speed=1.0f;
Point3D lookingAtPoint(-0.88,0,-0.48);
Point3D camPosition(200,0,109.5);
bool key_states[256];

void meteAxis() {
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-500.0f, 0.0f, 0.0f);
	glVertex3f( 500.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -500.0f, 0.0f);
	glVertex3f(0.0f,  500.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -500.0f);
	glVertex3f(0.0f, 0.0f,  500.0f);
	
	glEnd();
	glEnable(GL_LIGHTING);
}

void drawFigure(Figure figure) {
	VBO vbo = buffers["../models/"+figure.filename];
	glBindBuffer(GL_ARRAY_BUFFER,vbo.vertixes);
 	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,vbo.normals);
	glNormalPointer(GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,vbo.texCoords);
	glTexCoordPointer(2,GL_FLOAT,0,0);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.indexes);
	figure.apply();
 	glDrawElements(GL_TRIANGLES,
 		vbo.indexCount, // número de índices a desenhar
 		GL_UNSIGNED_INT, // tipo de dados dos índices
 		0);// parâmetro não utilizado
	glColor3f(0,0,0);
	figure.reset();
}

void drawFigures(Group g) {
	glPushMatrix();
	for (auto& transform : g.transformations) {
		transform->applyTransform();
	}
	for (auto& modelFileName : g.models) {
		drawFigure(modelFileName.second);
	}
	for (auto& group : g.nestedGroups) {
		drawFigures(group);
	}
	glPopMatrix();
}

void processKeyboardInput() {
	Point3D horizontal_look=lookingAtPoint.crossProduct(Point3D(0,1,0)); // cross product entre o look e o eixo y de modo a ter apenas o ponto para onde se deve dirigir horizontalmente
	if (key_states['w'])
			camPosition+=lookingAtPoint*speed;
	if (key_states['a'])
			camPosition-=horizontal_look*speed;
	if (key_states['s'])
			camPosition-=lookingAtPoint*speed;
	if (key_states['d'])
			camPosition+=horizontal_look*speed;
	if (key_states['g'])
			speed+=0.1f;
	if (key_states['f'])
			speed-=speed>0.1?0.1f:0;
	if (key_states['-']) 
			Transform::time_multiplier+=0.01;		
	if (key_states['+']) 
			Transform::time_multiplier-=Transform::time_multiplier>0.02?0.01:0;
}

void renderScene(void) {
	processKeyboardInput();

	// clear buffers
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camPosition.x,camPosition.y,camPosition.z, 
		      lookingAtPoint.x+camPosition.x,lookingAtPoint.y+camPosition.y,lookingAtPoint.z+camPosition.z,
			  0.0f,1.0f,0.0f);

	lights[0]->applyLight();
// put drawing instructions here
	if (axis) meteAxis();
	for (auto& g : groups) {
		drawFigures(g);
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

	//modifica o offset consoante a sensibilidade
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	//modifica o ângulo do ponto para o qual está a olhar
	yaw+=xoffset;
	pitch+=yoffset;
	
	// manter o pitch dentro de -90 a 90
	if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

	//calcula o novo ponto para o qual está a olhar de forma normalizada
    lookingAtPoint.x = cosf(radians(yaw)) * cosf(radians(pitch));
    lookingAtPoint.y = sinf(radians(pitch));
    lookingAtPoint.z = sinf(radians(yaw)) * cosf(radians(pitch));
}

void readFile3D(std::string filename) {
	VBO vbo = VBO();
	std::ifstream fp(filename);
	int numVertexes, numTriangles;
	float x,y,z;
	std::string line;
	std::getline(fp,line);
	std::istringstream iss(line);
	iss >> numVertexes >> numTriangles;
	std::vector<float> vertixes;
	std::vector<unsigned int> indexes;
	std::vector<float> normals;
	std::vector<float> textureCoordinates;
	int i;
	// Aquisição dos Pontos de Desenho dos Triangles do ficheiro
	for(i = 0; i < numVertexes; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> x >> y >> z)) {
			std::cout << "Erro a ler vértices do ficheiro! \n";
			break;
		}
		//adição dos valores x y e z de cada ponto a vetor de vértices
		vertixes.push_back(x);
		vertixes.push_back(y);
		vertixes.push_back(z);
	}
	glBindBuffer(GL_ARRAY_BUFFER,vbo.vertixes); //liga o buffer pontos ao array
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*vertixes.size(), vertixes.data(), GL_STATIC_DRAW);
	vbo.vertixCount=vertixes.size();
	// Aquisição dos Triangles a partir de 3 Pontos do Ficheiro
	int indicePonto1, indicePonto2, indicePonto3;
	for(i = 0; i < numTriangles; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> indicePonto1 >> indicePonto2 >> indicePonto3)) {
			std::cout << "Erro a ler índices do triangulo do ficheiro! \n";
			break;
		}
		//adição do índice de cada ponto do triângulo ao vetor de índices
		indexes.push_back(indicePonto1);
		indexes.push_back(indicePonto2);
		indexes.push_back(indicePonto3);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo.indexes); //liga o buffer indices ao array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * indexes.size(),indexes.data(),GL_STATIC_DRAW);
 	vbo.indexCount = indexes.size();
	float normalX, normalY, normalZ;
	for(i = 0; i < numVertexes; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> normalX >> normalY >> normalZ)) {
			std::cout << "Erro a ler normais do ficheiro! \n";
			break;
		}
		normals.push_back(normalX);
		normals.push_back(normalY);
		normals.push_back(normalZ);
	}
	glBindBuffer(GL_ARRAY_BUFFER,vbo.normals); //liga o buffer indices ao array
	glBufferData(GL_ARRAY_BUFFER,sizeof(float) * normals.size(),normals.data(),GL_STATIC_DRAW);
	float texX, texY;
	for(i = 0; i < numVertexes; i++) {
		std::getline(fp,line);
		std::istringstream iss(line);
		if(!(iss >> texX >> texY)) {
			std::cout << "Erro a ler texturas do ficheiro! \n";
			break;
		}
		//adição do índice de cada ponto do triângulo ao vetor de índices
		textureCoordinates.push_back(texX);
		textureCoordinates.push_back(texY);
	}
	glBindBuffer(GL_ARRAY_BUFFER,vbo.texCoords); //liga o buffer indices ao array
	glBufferData(GL_ARRAY_BUFFER,sizeof(float) * textureCoordinates.size(),textureCoordinates.data(),GL_STATIC_DRAW);
	buffers[filename]=vbo;
}

void readConfig(int argc, char **argv) {
	std::string name;
	xmlContent parser;
	if(argc == 2) {
		name = "../configs/" + std::string(argv[1]);
		parser = xmlContent(name);
	}
	else {
		parser = xmlContent();
	}
	groups=parser.parse();
	std::unordered_set<std::string> files = parser.getModels(); //é um set para evitar repetidos
	for(auto& filename : files) {
		std::string model = "../models/" + filename;
		readFile3D(model);
	}
	lights=parser.getLights();
}

void registerKeyDown(unsigned char key, int x, int y) {
	key_states[key]=true;
	if (key=='q')
		axis=!axis;
	if (key=='p') {
		glPolygonMode( GL_FRONT_AND_BACK, wire?GL_LINE:GL_FILL );
		wire=!wire;
	}
	if (key=='c') {
		Translation::showCurves=!Translation::showCurves;
	}
	if (key==' ')
		Transform::paused=!Transform::paused;
	if (key=='r')
		Transform::retroceder=-1*Transform::retroceder;
}

void registerKeyUp(unsigned char key, int x, int y) {
	key_states[key]=false;
}

void init() {
	lookingAtPoint.x = cosf(radians(yaw)) * cosf(radians(pitch));
    lookingAtPoint.y = sinf(radians(pitch));
    lookingAtPoint.z = sinf(radians(yaw)) * cosf(radians(pitch));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
}

int main(int argc, char **argv) {
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
	#ifndef __APPLE__
	glewInit();
	#endif
	
// put here the registration of the keyboard callbacks
	glutIgnoreKeyRepeat(GL_TRUE);
	glutKeyboardFunc(registerKeyDown);
	glutKeyboardUpFunc(registerKeyUp);
	glutPassiveMotionFunc(mouseControls);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// Initializations
	init();
	readConfig(argc,argv); //lê o xml e configura os VBO's
	
// enter GLUT's main cycle
	glutMainLoop();
	return 1;
}
