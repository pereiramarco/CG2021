#pragma once
#include <string>

class Ponto3D {
public:
	float x;
	float y;
	float z;
	int index; //serve para identificar que índice o Ponto tem
	Ponto3D();
	Ponto3D(float x1,float y1, float z1);
	Ponto3D(float x1,float y1, float z1,int indexG);
	Ponto3D* clone();
	std::string getCoords();
};