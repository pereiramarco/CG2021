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
    // Clock wise or Counter Clock wise
    cc=ccG==2?1:-1;
    axisX=axisXG;
    axisY=axisYG;
    axisZ=axisZG;
    type=2;
}

std::vector<float> Rotation::applyTransform() {
    int t=glutGet(GLUT_ELAPSED_TIME);
    if (type==2) {
        float delta_time = t-t_before;
        // Os graus a rodar têm de ter em conta o tempo passado, bem como se queremos a simulação a retroceder (valor -1)
        // e se a simulação está parada (multiplica por 0)
        degrees+=(360.0/(time*time_multiplier))*delta_time*!paused*retroceder;
        //std::cout<<"Angle: " << degrees << "\n";
    }
    glRotatef(degrees*cc,axisX,axisY,axisZ);
    t_before=t;
    std::vector<float> ret;
    ret.push_back(2.0f);
    ret.push_back(axisX);
    ret.push_back(axisY);
    ret.push_back(axisZ);
    ret.push_back(degrees*cc);
    return ret;
}