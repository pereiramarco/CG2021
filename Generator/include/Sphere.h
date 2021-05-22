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
    std::vector<Point3D> vertexes;
    std::vector<Triangle> faces;
    std::map<std::pair<int,int>,Point3D> points;
    std::vector<Point3D> normals;
    std::vector<std::pair<float,float>> texCoords;
    void addTopOrBottomSlice(bool top,int slice,int stack);
    void addSquareSlice(int slice,int stack);
public:
    Sphere();
    Sphere(int radiusG,int slicesG,int stacksG);
    std::shared_ptr<Model> generate();
};