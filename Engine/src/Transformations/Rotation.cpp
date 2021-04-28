#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Rotation.h"

Rotation::Rotation(const Rotation& r) {
    degrees=r.degrees;
    time=r.time;
    axisX=r.axisX;
    axisY=r.axisY;
    axisZ=r.axisZ;
}

Rotation::Rotation(int type,float degreesOrTimeG, float axisXG, float axisYG, float axisZG) {
    if (type) {
        degrees=degreesOrTimeG;
    }
    else {
        time=degreesOrTimeG;
    }
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
}

void Rotation::applyTransform() {
    glRotatef(degrees,axisX,axisY,axisZ);
}