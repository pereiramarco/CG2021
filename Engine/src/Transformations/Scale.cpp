#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Scale.h"

Scale::Scale(const Scale& s) {
    xScale=s.xScale;
    yScale=s.yScale;
    zScale=s.zScale;
}

Scale::Scale(float xG, float yG, float zG) {
    xScale=xG;
    yScale=yG;
    zScale=zG;
} 

std::vector<float> Scale::applyTransform() {
    std::vector<float> ret;
    ret.push_back(1);
    ret.push_back(xScale);
    ret.push_back(yScale);
    ret.push_back(zScale);
    glScalef(xScale,yScale,zScale);
    return ret;
}