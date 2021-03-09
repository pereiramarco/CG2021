#pragma once
#include "../../Utils/Triangulo.h"
#include "../../Utils/Ponto3D.h"
#include "Model.h"
#include <tuple>
#include <vector>
#include <string>
#include <map>

class Plane{
public:
    Plane();
    Plane(int sideG);
    Model* generate();
private:
    int side;
    Triangulo * t1,*t2;
    Ponto3D * topRight,*topLeft,*bottomLeft,*bottomRight;
};