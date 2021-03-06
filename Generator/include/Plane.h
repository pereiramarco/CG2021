#pragma once
#include "Triangulo.h"
#include "Ponto3D.h"
#include "Model.h"
#include <tuple>
#include <vector>
#include <string>
#include <map>

class Plane{
public:
    Plane();
    Plane(int widthG,int depthG);
    Model* generate();
private:
    int width,depth;
    Triangulo * t1,*t2;
    Ponto3D * topRight,*topLeft,*bottomLeft,*bottomRight;
};