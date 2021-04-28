#pragma once
#include "Triangle.h"
#include "../../Utils/Point3D.h"
#include "Model.h"
#include <memory>
#include <tuple>
#include <vector>
#include <string>
#include <map>

class Plane{
public:
    Plane();
    Plane(int sideG);
    std::shared_ptr<Model> generate();
private:
    int side;
    Triangle t1,t2;
    Point3D topRight,topLeft,bottomLeft,bottomRight;
};