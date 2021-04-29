#include "Point3D.h"
#include <string>


Point3D::Point3D(){
	x=0;y=0;z=0;index=0;
}

Point3D::Point3D(float x1,float y1, float z1) {
	x=x1;y=y1;z=z1;
}

Point3D::Point3D(float x1,float y1, float z1,int indexG) {
	x=x1;y=y1;z=z1;index=indexG;
}

Point3D::Point3D(const Point3D& p) {
	x=p.x;
	y=p.y;
	z=p.z;
	index=p.index;
}

void Point3D::zero() {
	x=0;
	y=0;
	z=0;
}

void Point3D::operator-=(Point3D& p) {
	x-=p.x;
	y-=p.y;
	z-=p.z;
}
void Point3D::operator+=(Point3D& p) {
	x+=p.x;
	y+=p.y;
	z+=p.z;
}

Point3D& Point3D::operator+(Point3D& p) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(this->x+p.x,this->y+p.y,this->z+p.z);
    return *res;
}

Point3D& Point3D::operator*(Point3D& r) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(x*r.x,y*r.y,z*r.z);
    return *res;
}

Point3D& Point3D::operator*(const float& r) {
	std::shared_ptr<Point3D> res = std::make_shared<Point3D>(x*r,y*r,z*r);
    return *res;
}

std::string Point3D::getCoords() {
	return "\n	X: "+std::to_string(x)+"\n	Y: "+std::to_string(y)+"\n	Z: "+std::to_string(z);
}