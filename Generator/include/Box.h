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
    std::vector<Triangle> faces;
    std::vector<Point3D> points;
    std::vector<Point3D> normals;
    int index;
    void addYLayer(bool top);
    void addXLayer(bool top);
    void addZLayer(bool top);
    void addSquare(bool top,Point3D topRight,Point3D topLeft,Point3D bellowLeft,Point3D bellowRight);
};