#include "../include/Plane.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>

using namespace std;


Plane::Plane() {
    width=5;
    depth=5;
}
Plane::Plane(int widthG,int depthG) {
    width=widthG;
    depth=depthG;
}
void Plane::generate() {
    float x=width/2.0;
    float z=depth/2.0;
    topRight=new Ponto3D(x,0,-z);
    topLeft=new Ponto3D(-x,0,-z);
    bottomLeft=new Ponto3D(-x,0,z);
    bottomRight=new Ponto3D(x,0,z);
    t1=new Triangulo(topRight,topLeft,bottomLeft,new Ponto3D(1,0,0));
    t2=new Triangulo(topRight,bottomLeft,bottomRight,new Ponto3D(0,1,0));
}


void Plane::saveToFile(string filename) {
    ofstream fout(filename, ios::out) ; 
    fout<< "plane\n";
    fout << to_string(topRight->x) << " " << to_string(topRight->y) << " " << to_string(topRight->z) << "\n";
    fout << to_string(topLeft->x) << " " << to_string(topLeft->y) << " " << to_string(topLeft->z) << "\n";
    fout << to_string(bottomLeft->x) << " " << to_string(bottomLeft->y) << " " << to_string(bottomLeft->z) << "\n";
    fout << to_string(bottomRight->x) << " " << to_string(bottomRight->y) << " " << to_string(bottomRight->z) << "\n";
}

void Plane::draw() {
    t1->desenha();
    t2->desenha();
}