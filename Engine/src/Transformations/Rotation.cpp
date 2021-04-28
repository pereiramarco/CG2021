#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Rotation.h"
#include "stdio.h"

Rotation::Rotation(const Rotation& r) {
    degrees=r.degrees;
    time=r.time;
    axisX=r.axisX;
    axisY=r.axisY;
    axisZ=r.axisZ;
}

Rotation::Rotation(float degreesG, float axisXG, float axisYG, float axisZG) {
    degrees=degreesG;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
    cc=1;
}

Rotation::Rotation(float timeG, int ccG ,float axisXG, float axisYG, float axisZG) {    
    time=timeG*1000;
    cc=ccG==2?1:-1;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
}

void Rotation::applyTransform() {
    int t=glutGet(GLUT_ELAPSED_TIME);
    if (time) {
        float delta_time = t-t_before;
        degrees+=(float)(360.0/time)*delta_time;
    }
    glRotatef(degrees*cc,axisX,axisY,axisZ);
    t_before=t;
}