#pragma once
#include "Transform.h"

class Rotation : public Transform {
public:    
    double degrees;
    float axisX;
    float axisY;
    float axisZ;
    float time;
    int t_before;
    int cc;
    int type;

    Rotation(const Rotation& r);
    Rotation(double degreesG, float axisXG, float axisYG, float axisZG);
    Rotation(double timeG, int ccG ,float axisXG, float axisYG, float axisZG);
    void applyTransform();

};