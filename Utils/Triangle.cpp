#include "Triangle.h"
#include "iostream"

using namespace std;

Triangle::Triangle() {
    ponto1=new Point3D();
    ponto2=new Point3D();
    ponto3=new Point3D(); 
	redValue = greenValue = blueValue = 1.0f;
}

Triangle::Triangle(Point3D *ponto11,Point3D *ponto22,Point3D *ponto33) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
    redValue = greenValue = blueValue = 1.0f;
}

Triangle::Triangle(Point3D *ponto11,Point3D *ponto22,Point3D *ponto33,float redV,float greenV,float blueV) {
    ponto1=ponto11;
    ponto2=ponto22;
    ponto3=ponto33;
    redValue = redV;
    greenValue = greenV;
    blueValue = blueV;
}

void Triangle::printCoords() {
	std::cout<< "CIMA: " << ponto1->getCoords() << "\nESQ: " << ponto2->getCoords() << "\nDIR: "<< ponto3->getCoords() << "\n";
}
