#include "../include/Box.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
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
        t1=new Triangulo(topRight,topLeft,bellowLeft,new Ponto3D(0.0f,1.0f,0.0f));
        t2=new Triangulo(topRight,bellowLeft,bellowRight,new Ponto3D(1.0f,0.0f,0.0f));
    }
    else {
        t1=new Triangulo(topRight,bellowLeft,topLeft,new Ponto3D(0.0f,1.0f,0.0f));
        t2=new Triangulo(topRight,bellowRight,bellowLeft,new Ponto3D(1.0f,0.0f,0.0f));
    }
    faces.push_back(t1);
    faces.push_back(t2);
}

void Box::addYLayer(int iterations,bool top) { 
    int y=top?0:iterations;
    for (int x=0;x<iterations;x++) {
        for (int z=0;z<iterations;z++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x+1,y,z)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y,z+1)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x+1,y,z+1)];
            addSquare(!top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addXLayer(int iterations,bool top) {
    int x=top?0:iterations;
    for (int y=0;y<iterations;y++) {
        for (int z=0;z<iterations;z++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x,y,z+1)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y+1,z)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x,y+1,z+1)];
            addSquare(!top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addZLayer(int iterations,bool top) {
    int z=top?0:iterations;
    for (int x=0;x<iterations;x++) {
        for (int y=0;y<iterations;y++) {
            Ponto3D * topLeft=points[tuple<int,int,int>(x,y,z)];
            Ponto3D * topRight=points[tuple<int,int,int>(x+1,y,z)];
            Ponto3D * bellowLeft=points[tuple<int,int,int>(x,y+1,z)];
            Ponto3D * bellowRight=points[tuple<int,int,int>(x+1,y+1,z)];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::generate() {
    float x_increment=1.0*width/(1.0*nDivisions+1);
    float y_increment=1.0*height/(1.0*nDivisions+1);
    float z_increment=1.0*depth/(1.0*nDivisions+1);
    for (int y=0;y<=nDivisions+1;y++) {
        for (int x=0;x<=nDivisions+1;x++) {
            for (int z=0;z<=nDivisions+1;z++) {
                if (y==0 || y==nDivisions+1 || (x==0 || x==nDivisions+1) || (z==0 || z==nDivisions+1)) { 
                    Ponto3D * p = new Ponto3D(x*x_increment,y*y_increment,z*z_increment);
                    tuple<int,int,int> t(x,y,z);
                    points[t]=p;
                }
            }
        }
    }
    addYLayer(nDivisions+1,false);
    addYLayer(nDivisions+1,true);
    addXLayer(nDivisions+1,false);
    addXLayer(nDivisions+1,true);
    addZLayer(nDivisions+1,false);
    addZLayer(nDivisions+1,true);
}

void Box::saveToFile(string filename) {
    ofstream fout(filename, ios::out) ; 
    fout<< "box\n" << to_string(nDivisions) << "\n";
    for (int i=0;i<=nDivisions+1;i++) {
        for (int j=0;j<=nDivisions+1;j++) {
            for (int k=0;k<=nDivisions+1;k++) {
                Ponto3D* p = points[tuple<int,int,int>(i,j,k)];
                if (p!=NULL)
                    fout<< to_string(i) << " " << to_string(j) << " " << to_string(k) << " " << to_string(p->x) << " " << to_string(p->y) << " " << to_string(p->z) << "\n";
            } 
        }
    }
    
}

void Box::draw() {
    for (auto& t: faces) {
        t->desenha();
    }
}