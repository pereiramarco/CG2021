#include "../include/Box.h"
#include "../../Utils/Ponto3D.h"
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

using namespace std;

Box::Box() {
    nDivisions=0;
    width=10;
    depth=10;
    height=10;
}

Box::Box(int widthG,int depthG,int heightG,int nDivisionsG) {
    width=widthG;
    depth=depthG;
    height=heightG;
    nDivisions=nDivisionsG;
}

void Box::addSquare(bool top,Ponto3D * topRight,Ponto3D * topLeft,Ponto3D * bellowLeft,Ponto3D * bellowRight) {
    Triangulo *t1,*t2;
    if (top) {
        t1=new Triangulo(topRight,topLeft,bellowLeft);
        t2=new Triangulo(topRight,bellowLeft,bellowRight);
    }
    else {
        t1=new Triangulo(topRight,bellowLeft,topLeft);
        t2=new Triangulo(topRight,bellowRight,bellowLeft);
    }
    faces.push_back(t1);
    faces.push_back(t2);
}

void Box::addYLayer(bool top) { 
    int y=top?0:nDivisions;
    for (int x=0;x<nDivisions;x++) {
        for (int z=0;z<nDivisions;z++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x+1,y,z)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y,z+1)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x+1,y,z+1)];
            addSquare(!top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addXLayer(bool top) {
    int x=top?0:nDivisions;
    for (int y=0;y<nDivisions;y++) {
        for (int z=0;z<nDivisions;z++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x,y,z+1)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y+1,z)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x,y+1,z+1)];
            addSquare(!top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addZLayer(bool top) {
    int z=top?0:nDivisions;
    for (int x=0;x<nDivisions;x++) {
        for (int y=0;y<nDivisions;y++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x+1,y,z)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y+1,z)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x+1,y+1,z)];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

Model* Box::generate() {
    float x_increment=1.0*width/(1.0*nDivisions);
    float y_increment=1.0*height/(1.0*nDivisions);
    float z_increment=1.0*depth/(1.0*nDivisions);
    int index=0;
    vector<Ponto3D*> vertixes;
    for (int y=0;y<=nDivisions;y++) {
        for (int x=0;x<=nDivisions;x++) {
            for (int z=0;z<=nDivisions;z++) {
                if (y==0 || y==nDivisions || x==0 || x==nDivisions || z==0 || z==nDivisions) { 
                    Ponto3D * p = new Ponto3D(x*x_increment,y*y_increment,z*z_increment,index++);
                    vertixes.push_back(p);
                    tuple<int,int,int> t(x,y,z);
                    points[t]=p;
                }
            }
        }
    }
    addYLayer(false);
    addYLayer(true);
    addXLayer(false);
    addXLayer(true);
    addZLayer(false);
    addZLayer(true);
    return new Model(vertixes.size(),faces.size(),vertixes,faces);
}