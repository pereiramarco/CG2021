#include "Ponto3D.h"
#include <string>

Ponto3D::Ponto3D(){
	x=0;y=0;z=0;index=0;
}

Ponto3D::Ponto3D(float x1,float y1, float z1) {
	x=x1;y=y1;z=z1;
}

Ponto3D::Ponto3D(float x1,float y1, float z1,int indexG) {
	x=x1;y=y1;z=z1;index=indexG;
}

std::string Ponto3D::getCoords() {
	return "\n	X: "+std::to_string(x)+"\n	Y: "+std::to_string(y)+"\n	Z: "+std::to_string(z);
}