#pragma once
#include "Transform.h"

class Rotation : public Transform {
public:    
    float degrees;
    float axisX;
    float axisY;
    float axisZ;
    float time;

    Rotation(const Rotation& r);
    Rotation(int type,float degreesOrTimeG, float axisXG, float axisYG, float axisZG);
    void applyTransform();

};