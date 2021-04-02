#pragma once
#include "Transform.h"

class Rotation : public Transform {
public:    
    float degrees;
    float axisX;
    float axisY;
    float axisZ;

    Rotation(float degreesG, float axisXG, float axisYG, float axisZG);
    void applyTransform();

};