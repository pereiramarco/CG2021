#include <cstdlib>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Lights/PointLight.h"

PointLight::PointLight() {
    pointX = pointY = pointZ = 0;
}

PointLight::PointLight(float x, float y, float z) {
    pointX=x;
    pointY=y;
    pointZ=z;
}

void PointLight::applyLight() {
    float pos[4] = {pointX,pointY,pointZ,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
}