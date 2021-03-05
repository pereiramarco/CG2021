#pragma once
#include "Triangulo.h"
#include <vector>
#include "Ponto3D.h"
#include <string>
#include <tuple>
#include <map>

class Box{
public:
    Box();
    Box(int widthG,int depthG,int heightG,int nDivisionsG);
    void generate();
    void draw();
    void saveToFile(std::string filename);
private:
    int width,depth,height,nDivisions;
    std::vector<Triangulo*> faces;
    std::map<std::tuple<int,int,int>,Ponto3D*> points;
    void addYLayer(int iterations,bool top);
    void addXLayer(int iterations,bool top);
    void addZLayer(int iterations,bool top);
    void addSquare(bool top,Ponto3D * topRight,Ponto3D * topLeft,Ponto3D * bellowLeft,Ponto3D * bellowRight);
};