#pragma once
#include "Triangle.h"
#include "../../Utils/Point3D.h"
#include "Model.h"
#include <memory>
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include "iostream"

class Patch {
public:
    Patch()=default;
    std::vector<std::vector<Point3D>> points; 
};