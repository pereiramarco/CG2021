#pragma once
#include "Light.h"

// TODO
class SpotLight : public Light {
public:
    float pointX, pointY, pointZ;
    float dirX, dirY, dirZ;
    float angle; 
    SpotLight();
    SpotLight(float px, float py, float pz, float dx, float dy, float dz, float ang);
    void applyLight();
};