#pragma once
#include "Light.h"

class PointLight : public Light {
public:
    float pointX, pointY, pointZ;
    PointLight();
    PointLight(float x, float y, float z);
    void applyLight();
};