#pragma once
#include "../../Utils/Point3D.h"
#include <memory>

class Triangle{
public:
    std::shared_ptr<Point3D> ponto1,ponto2,ponto3;
    Triangle();
    Triangle(std::shared_ptr<Point3D> point11,std::shared_ptr<Point3D> point22,std::shared_ptr<Point3D> point33);
	void printCoords();
};