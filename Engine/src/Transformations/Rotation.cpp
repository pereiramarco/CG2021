#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Rotation.h"

Rotation::Rotation(float degreesG, float axisXG, float axisYG, float axisZG) {
    degrees=degreesG;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
}

void Rotation::applyTransform() {
    glRotatef(degrees,axisX,axisY,axisZ);
}