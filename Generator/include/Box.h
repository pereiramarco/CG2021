#pragma once
#include "Triangulo.h"
#include "Model.h"
#include <tuple>
#include <vector>
#include <map>

class Box{
public:
    Box();
    Box(int widthG,int depthG,int heightG,int nDivisionsG);
    void generate();
    void draw();
    void saveToFile(string filename);
private:
    int width,depth,height,nDivisions;
    vector<Triangulo*> faces;
    map<tuple<int,int,int>,Ponto3D*> points;
    void addYLayer(int iterations,bool top);
    void addXLayer(int iterations,bool top);
    void addZLayer(int iterations,bool top);
    void addSquare(bool top,Ponto3D * topRight,Ponto3D * topLeft,Ponto3D * bellowLeft,Ponto3D * bellowRight);
};