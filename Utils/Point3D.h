#pragma once
#include <string>
#include <memory>

class Point3D {
public:
	float x;
	float y;
	float z;
	int index; //serve para identificar que índice o Ponto tem
	Point3D();
	Point3D(float x1,float y1, float z1);
	Point3D(float x1,float y1, float z1,int indexG);
	Point3D(const Point3D& p);
	void zero();

	Point3D& operator*(const float& r);
	Point3D& operator+(Point3D& p);
	void operator+=(Point3D& p);
	void operator-=(Point3D& p);
	std::string getCoords();
};