#pragma once
#include "Triangle.h"
#include "../../Utils/Point3D.h"
#include "Model.h"
#include "Patch.h"
#include <memory>
#include <tuple>
#include <vector>
#include <string>
#include <map>

class Bezier{
public:
    Bezier();
    Bezier(std::string patch_file,int tesselation_level);
    void read_patches();
    std::shared_ptr<Model> generate();
private:
    int vertical_tesselation;
    float vertical_tesselation_inc;
    int horizontal_tesselation;
    float horizontal_tesselation_inc;
    std::vector<std::vector<Point3D>> bezier_matrix;
    std::string patch_file;
    std::vector<Patch> patches;
    int numPatches;
    void calculatePoints(std::vector<std::vector<Point3D>> preCalculatedMatrix,int& indexPoint,std::vector<Point3D>& vertixes,std::vector<Triangle>& triangs);
    Point3D calculatePoint(std::vector<std::vector<Point3D>> preCalculatedMatrix,int vertical_level,int horizontal_level);
    std::vector<std::vector<Point3D>> multiplyMatrix(std::vector<std::vector<Point3D>> m1, std::vector<std::vector<Point3D>> m2);
};