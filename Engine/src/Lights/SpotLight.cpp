#include <cstdlib>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Lights/SpotLight.h"

SpotLight::SpotLight() {
    pointX = pointY = pointZ = 0;
    dirX = dirY = dirZ = 0;
    angle = 0;
}

SpotLight::SpotLight(float px, float py, float pz, float dx, float dy, float dz, float ang) {
    pointX=px;
    pointY=py;
    pointZ=pz;
    dirX=dx;
    dirY=dy;
    dirZ=dz;
    angle=ang;
}

void SpotLight::applyLight() {
    float pos[4] = {pointX,pointY,pointZ,1.0};
    float dir[3] = {dirX,dirY,dirZ};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,angle);
}