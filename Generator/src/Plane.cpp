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
    std::vector<std::shared_ptr<Point3D>> vertixes;
    std::vector<std::shared_ptr<Triangle>> faces;
    float x=side/2.0;
    float z=side/2.0;
    topRight=std::make_shared<Point3D>(x,0,-z,0);vertixes.push_back(topRight);
    topLeft=std::make_shared<Point3D>(-x,0,-z,1);vertixes.push_back(topLeft);
    bottomLeft=std::make_shared<Point3D>(-x,0,z,2);vertixes.push_back(bottomLeft);
    bottomRight=std::make_shared<Point3D>(x,0,z,3);vertixes.push_back(bottomRight);
    t1=std::make_shared<Triangle>(topRight,topLeft,bottomLeft);faces.push_back(t1);
    t2=std::make_shared<Triangle>(topRight,bottomLeft,bottomRight);faces.push_back(t2);
    return std::make_shared<Model>(vertixes,faces);
}