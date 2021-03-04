#ifdef __TRIANGULO__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../include/Triangulo.h"
#include "iostream"

using namespace std;

Triangulo::Triangulo() {
    ponto1=new Ponto3D();
    ponto2=new Ponto3D();
    ponto3=new Ponto3D(); 
	cor = new Ponto3D(1.0f,1.0f,1.0f);
}

Triangulo::Triangulo(Ponto3D *ponto11,Ponto3D *ponto22,Ponto3D *ponto33) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
    cor = new Ponto3D(1.0f,1.0f,1.0f);
}

Triangulo::Triangulo(Ponto3D *ponto11,Ponto3D *ponto22,Ponto3D *ponto33,Ponto3D* corG) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
	cor = corG;
}

void Triangulo::desenha() {

    glColor3f(cor->x,cor->y,cor->z);
    glVertex3f(ponto1->x,ponto1->y,ponto1->z);
    glVertex3f(ponto2->x,ponto2->y,ponto2->z);
    glVertex3f(ponto3->x,ponto3->y,ponto3->z);
	glColor3f(1,1,1);
}
    

void Triangulo::printCoords() {
	std::cout<< "CIMA: " << ponto1->getCoords() << "\nESQ: " << ponto2->getCoords() << "\nDIR: "<< ponto3->getCoords() << "\n";
}
