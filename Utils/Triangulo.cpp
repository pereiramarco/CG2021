#include "Triangulo.h"
#include "iostream"

using namespace std;

Triangulo::Triangulo() {
    ponto1=new Ponto3D();
    ponto2=new Ponto3D();
    ponto3=new Ponto3D(); 
	redValue = greenValue = blueValue = 1.0f;
}

Triangulo::Triangulo(Ponto3D *ponto11,Ponto3D *ponto22,Ponto3D *ponto33) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
    redValue = greenValue = blueValue = 1.0f;
}

Triangulo::Triangulo(Ponto3D *ponto11,Ponto3D *ponto22,Ponto3D *ponto33,float redV,float greenV,float blueV) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
    redValue = redV;
    greenValue = greenV;
    blueValue = blueV;
}

void Triangulo::printCoords() {
	std::cout<< "CIMA: " << ponto1->getCoords() << "\nESQ: " << ponto2->getCoords() << "\nDIR: "<< ponto3->getCoords() << "\n";
}
