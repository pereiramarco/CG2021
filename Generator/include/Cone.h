#pragma once
#include "Triangle.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include "Model.h"
#include <string>
#include <map>
#include <memory>

class Cone{
public:
    Cone();
    Cone(int radius,int heightG,int nSlicesG,int nStacksG);
    std::shared_ptr<Model> generate();
private:
    int radiusBase,height,nStacks,nSlices;
    std::vector<std::shared_ptr<Triangle>> faces;
    std::map<std::pair<int,int>,std::shared_ptr<Point3D>> points;
    void addTopSlice(int slice,int stack,int not_last);
    void addCircleSlice(int slice,int stack,int not_last);
    void addSquareSlice(int slice,int stack,int not_last);
};