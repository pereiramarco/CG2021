#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Rotation.h"
#include "iostream"

Rotation::Rotation(const Rotation& r) {
    degrees=r.degrees;
    time=r.time;
    axisX=r.axisX;
    axisY=r.axisY;
    axisZ=r.axisZ;
    cc=r.cc;
    type=r.type;
}

Rotation::Rotation(double degreesG, float axisXG, float axisYG, float axisZG) {
    degrees=degreesG;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
    cc=1;
    type=1;
}

Rotation::Rotation(double timeG, int ccG ,float axisXG, float axisYG, float axisZG) {    
    time=timeG*1000.0;
    cc=ccG==2?1:-1;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
    type=2;
}

void Rotation::applyTransform() {
    int t=glutGet(GLUT_ELAPSED_TIME);
    if (type==2) {
        float delta_time = t-t_before;
        degrees+=(360.0/(time*time_multiplier))*delta_time*!paused*retroceder;
        //std::cout<<"Angle: " << degrees << "\n";
    }
    glRotatef(degrees*cc,axisX,axisY,axisZ);
    t_before=t;
}