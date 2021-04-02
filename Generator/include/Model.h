#pragma once
#include "Triangle.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include <string>
#include <map>
#include <memory>

class Model{
public:
    Model(std::vector<std::shared_ptr<Point3D>> vertixesG,std::vector<std::shared_ptr<Triangle>> faces);
    void saveToFile(std::string filename);
private:
    int nVertices,nTriangulos;
    std::vector<std::shared_ptr<Triangle>> faces;
    std::vector<std::shared_ptr<Point3D>> vertixes;
};