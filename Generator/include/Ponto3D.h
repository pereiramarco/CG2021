#pragma once
#include <string>

class Ponto3D {
public:
	float x;
	float y;
	float z;
	Ponto3D();
	Ponto3D(float x1,float y1, float z1);
	Ponto3D* clone();
	std::string getCoords();
};