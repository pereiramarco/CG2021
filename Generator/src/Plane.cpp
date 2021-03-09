#include "../include/Plane.h"
#include "../../Utils/Ponto3D.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


Plane::Plane() {
    side=5;
}
Plane::Plane(int sideG) {
    side=sideG;
}
Model* Plane::generate() {
    vector<Ponto3D*> vertixes;
    vector<Triangulo*> faces;
    float x=side/2.0;
    float z=side/2.0;
    topRight=new Ponto3D(x,0,-z,0);vertixes.push_back(topRight);
    topLeft=new Ponto3D(-x,0,-z,1);vertixes.push_back(topLeft);
    bottomLeft=new Ponto3D(-x,0,z,2);vertixes.push_back(bottomLeft);
    bottomRight=new Ponto3D(x,0,z,3);vertixes.push_back(bottomRight);
    t1=new Triangulo(topRight,topLeft,bottomLeft);faces.push_back(t1);
    t2=new Triangulo(topRight,bottomLeft,bottomRight);faces.push_back(t2);
    return new Model(vertixes,faces);
}