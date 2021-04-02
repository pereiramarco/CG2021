#pragma once
#include "Transform.h"

class Translation : public Transform {
public:
    float x;
    float y;
    float z;

    Translation(float xG, float yG, float zG);
    void applyTransform();

};