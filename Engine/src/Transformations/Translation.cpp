#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../include/Transformations/Translation.h"

Translation::Translation(float xG, float yG, float zG) {
    x=xG;
    y=yG;
    z=zG;
} 

void Translation::applyTransform() {
    glTranslatef(x,y,z);
}