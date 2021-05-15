#include "../include/Plane.h"
#include "../../Utils/Point3D.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>

Plane::Plane() {
    side=5;
}
Plane::Plane(int sideG) {
    side=sideG;
}
std::shared_ptr<Model> Plane::generate() {
    std::vector<Point3D> vertixes;
    std::vector<Triangle> faces;
    std::vector<Point3D> normals;
    float x=side/2.0;
    float z=side/2.0;
    topRight=Point3D(x,0,-z,0);vertixes.push_back(topRight);
    topLeft=Point3D(-x,0,-z,1);vertixes.push_back(topLeft);
    bottomLeft=Point3D(-x,0,z,2);vertixes.push_back(bottomLeft);
    bottomRight=Point3D(x,0,z,3);vertixes.push_back(bottomRight);
    t1=Triangle(topRight.index,topLeft.index,bottomLeft.index);faces.push_back(t1);
    t2=Triangle(topRight.index,bottomLeft.index,bottomRight.index);faces.push_back(t2);
    for(int i = 0; i < 4; i++) {
        auto normal=Point3D(0,1,0);
        normals.push_back(normal);
    }
    return std::make_shared<Model>(vertixes,faces,normals);
}