#pragma once
#include "../../Utils/Point3D.h"
#include <memory>

class Triangle{
public:
    int indexP1,indexP2,indexP3;
    Triangle();
    Triangle(int indexP1, int indexP2, int indexP3);
};