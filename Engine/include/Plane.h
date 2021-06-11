#pragma once
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../Utils/Point3D.h"

class Plane {
private:
public:
    Plane()=default;
    void setCoefficients(float coef[4]);
    float distance(Point3D point);
    float coefficients[4];
};
