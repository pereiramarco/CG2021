#include <cstdlib>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight() {
    directionX = directionY = directionZ = 0;
}

DirectionalLight::DirectionalLight(float x, float y, float z) {
    directionX=x;
    directionY=y;
    directionZ=z;
}

void DirectionalLight::applyLight() {
    float pos[4] = {directionX,directionY,directionZ,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
}