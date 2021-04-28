#pragma once
#include "Transform.h"
#include "../../../Utils/Point3D.h"
#include <vector>
#include <memory>

class Translation : public Transform {
public:
    float x;
    float y;
    float z;
    float time;
    std::vector<std::shared_ptr<Point3D>> curve_points;

    Translation(float xG, float yG, float zG);
    Translation(float timeG,std::vector<std::shared_ptr<Point3D>> curve_pointsG);
    void applyTransform();

};