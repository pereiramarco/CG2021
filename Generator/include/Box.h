#pragma once
#include "Triangle.h"
#include "../../Utils/Point3D.h"
#include "Model.h"
#include <vector>
#include <string>
#include <tuple>
#include <map>

class Box{
public:
    Box();
    Box(int widthG,int depthG,int heightG,int nDivisionsG);
    std::shared_ptr<Model> generate();
private:
    int width,depth,height,nDivisions;
    std::vector<std::shared_ptr<Triangle>> faces;
    std::map<std::tuple<int,int,int>,std::shared_ptr<Point3D>> points;
    void addYLayer(bool top);
    void addXLayer(bool top);
    void addZLayer(bool top);
    void addSquare(bool top,std::shared_ptr<Point3D> topRight,std::shared_ptr<Point3D> topLeft,std::shared_ptr<Point3D> bellowLeft,std::shared_ptr<Point3D> bellowRight);
};