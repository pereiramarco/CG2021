#include "../include/Triangle.h"
#include "iostream"

Triangle::Triangle() {
    ponto1=std::make_shared<Point3D>();
    ponto2=std::make_shared<Point3D>();
    ponto3=std::make_shared<Point3D>(); 
}

Triangle::Triangle(std::shared_ptr<Point3D> point11,std::shared_ptr<Point3D> point22,std::shared_ptr<Point3D> point33) {
    ponto1=point11;
    ponto2=point22;
    ponto3=point33;
}

void Triangle::printCoords() {
	std::cout<< "CIMA: " << ponto1->getCoords() << "\nESQ: " << ponto2->getCoords() << "\nDIR: "<< ponto3->getCoords() << "\n";
}
