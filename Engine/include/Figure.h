#pragma once
#include <string>

class Figure {
public:
    float red;
    float green;
    float blue;
    std::string filename;

    Figure();
    Figure(const Figure& fig);
    Figure(float redG,float greenG,float blueG,std::string filenameG);

};