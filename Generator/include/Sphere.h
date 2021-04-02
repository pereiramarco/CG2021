#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../../Utils/Point3D.h"
#include <string>
#include "Triangle.h"
#include "Model.h"

class Sphere {
private:
    int radius,nStacks,nSlices;
    std::vector<std::shared_ptr<Triangle>> faces;
    std::map<std::pair<int,int>,std::shared_ptr<Point3D>> points;
    void addTopOrBottomSlice(bool top,int slice,int stack,int not_last);
    void addSquareSlice(int slice,int stack,int not_last);
public:
    Sphere();
    Sphere(int radiusG,int slicesG,int stacksG);
    std::shared_ptr<Model> generate();
};