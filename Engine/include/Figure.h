#pragma once
#include <string>
#include "../../Utils/Point3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Figure {
public:
    float diffR, diffG, diffB;
    float specR, specG, specB;
    float emissR, emissG, emissB;
    float ambR, ambG, ambB;
    float shininess;
    float radius;
    Point3D centerPoint;
    GLuint texID;
    std::string filename;

    Figure();
    Figure(const Figure& fig);
    Figure(int textureG, Point3D diff,Point3D spec,float shin,Point3D amb,Point3D emiss,std::string filenameG,float radiusG);
    void apply();
    void reset();
};