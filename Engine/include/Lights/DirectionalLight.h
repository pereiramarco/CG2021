#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
    float directionX, directionY, directionZ;
    DirectionalLight();
    DirectionalLight(float x, float y, float z);
    void applyLight();
};