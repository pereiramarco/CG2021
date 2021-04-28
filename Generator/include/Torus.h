#pragma once
#include <vector>
#include <map>
#include <memory>
#include "../../Utils/Point3D.h"
#include <string>
#include "Triangle.h"
#include "Model.h"

class Torus {
private:
    int widenessRadius,thicknessRadius,nRings,nSides;
    std::vector<Triangle> faces;
    std::map<std::pair<int,int>,Point3D> points;
public:
    Torus();
    Torus(int widenessRadiusG,int thicknessRadiusG,int ringsG,int sidesG);
    void addSquare(int ring,int side,int not_last_ring,int not_last_side);
    std::shared_ptr<Model> generate();
};