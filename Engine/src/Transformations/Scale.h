#pragma once
#include "Transform.h"

class Scale : public Transform {
public:
    float xScale;
    float yScale;
    float zScale;

    Scale(float xG, float yG, float zG);
    void applyTransform();

};