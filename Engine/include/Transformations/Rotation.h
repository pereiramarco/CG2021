#pragma once
#include "Transform.h"

class Rotation : public Transform {
public:    
    float degrees;
    float axisX;
    float axisY;
    float axisZ;
    float time;
    int t_before;
    int cc;
    static float time_multiplier;
    static bool paused;

    Rotation(const Rotation& r);
    Rotation(float degreesG, float axisXG, float axisYG, float axisZG);
    Rotation(float timeG, int ccG ,float axisXG, float axisYG, float axisZG);
    void applyTransform();

};