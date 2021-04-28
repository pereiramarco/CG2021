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

void Scale::applyTransform() {
    glScalef(xScale,yScale,zScale);
}