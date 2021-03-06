#include "../include/Plane.h"
#include "../../Utils/Ponto3D.h"
#include "../include/Model.h"
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES

using namespace std;


Plane::Plane() {
    width=5;
    depth=5;
}
Plane::Plane(int widthG,int depthG) {
    width=widthG;
    depth=depthG;
}
Model* Plane::generate() {
    vector<Ponto3D*> vertixes;
    vector<Triangulo*> faces;
    float x=width/2.0;
    float z=depth/2.0;
    topRight=new Ponto3D(x,0,-z,0);vertixes.push_back(topRight);
    topLeft=new Ponto3D(-x,0,-z,1);vertixes.push_back(topLeft);
    bottomLeft=new Ponto3D(-x,0,z,2);vertixes.push_back(bottomLeft);
    bottomRight=new Ponto3D(x,0,z,3);vertixes.push_back(bottomRight);
    t1=new Triangulo(topRight,topLeft,bottomLeft);faces.push_back(t1);
    t2=new Triangulo(topRight,bottomLeft,bottomRight);faces.push_back(t2);
    return new Model(vertixes.size(),faces.size(),vertixes,faces);
}