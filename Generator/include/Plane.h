#pragma once
#include <tuple>
#include <vector>
#include <map>
#include "Triangulo.h"
#include "Ponto3D.h"

class Plane{
public:
    Plane();
    Plane(int widthG,int depthG);
    void generate();
    void draw();
    void saveToFile(std::string filename);
private:
    int width,depth;
    Triangulo * t1,*t2;
    Ponto3D * topRight,*topLeft,*bottomLeft,*bottomRight;
};