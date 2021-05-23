#pragma once
#include "Triangle.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include <string>
#include <map>
#include <memory>

class Model{
public:
    Model(std::vector<Point3D> vertixesG,std::vector<Triangle> faces,std::vector<Point3D> normals,std::vector<std::pair<float,float>> texCoords);
    void saveToFile(std::string filename);
private:
    int nVertices,nTriangulos;
    std::vector<Triangle> facesT;
    std::vector<Point3D> vertixesT;
    std::vector<Point3D> normalsT;
    std::vector<std::pair<float,float>> texCoordsT;
};