#pragma once
#include <string>
#include "../../Utils/Point3D.h"

class Figure {
public:
    float diffR, diffG, diffB;
    float specR, specG, specB;
    float emissR, emissG, emissB;
    float ambR, ambG, ambB;
    float shininess;

    std::string filename;

    Figure();
    Figure(const Figure& fig);
    Figure(Point3D diff,Point3D spec,float shin,Point3D amb,Point3D emiss,std::string filenameG);
    void applyColor();
    void resetColor();
};