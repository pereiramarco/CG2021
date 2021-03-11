#pragma once
#include "../../Utils/Triangle.h"
#include "../../Utils/Point3D.h"
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
    Triangle * t1,*t2;
    Point3D * topRight,*topLeft,*bottomLeft,*bottomRight;
};