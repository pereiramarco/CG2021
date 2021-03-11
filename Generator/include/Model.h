#pragma once
#include "../../Utils/Triangle.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include <string>
#include <map>

class Model{
public:
    Model(std::vector<Point3D*> vertixesG,std::vector<Triangle*> faces);
    void saveToFile(std::string filename);
private:
    int nVertices,nTriangulos;
    std::vector<Triangle*> faces;
    std::vector<Point3D*> vertixes;
};