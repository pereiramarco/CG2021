#pragma once
#include "../../Utils/Point3D.h"
#include <memory>

class Triangle{
public:
    int indexP1,indexP2,indexP3;
    Triangle(std::shared_ptr<Point3D> point11,std::shared_ptr<Point3D> point22,std::shared_ptr<Point3D> point33);
	Triangle(int indexP1, int indexP2, int indexP3);
};