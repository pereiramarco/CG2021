#pragma once
#include "Point3D.h"

class Triangle{
public:
    Point3D *ponto1,*ponto2,*ponto3;
    float redValue, greenValue, blueValue;
    Triangle();
    Triangle(Point3D *point11,Point3D *point22,Point3D *point33);
	Triangle(Point3D *point11,Point3D *point22,Point3D *point33,float redV,float greenV,float blueV);
	void printCoords();
};