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
    int widenessRadius,thicknessRadius,nRings,nSides,index;
    std::vector<Point3D> vertexes;
    std::vector<Triangle> faces;
    std::map<std::pair<int,int>,Point3D> points;
    std::vector<Point3D> normals;
    std::vector<std::pair<float,float>> texCoords;
public:
    Torus();
    Torus(int widenessRadiusG,int thicknessRadiusG,int ringsG,int sidesG);
    void addSquare(int ring,int side,int not_last_ring,int not_last_side);
    void constructRing(int ring, float ring_angle);
    std::shared_ptr<Model> generate();
};