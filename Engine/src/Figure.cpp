#include "../include/Figure.h"

Figure::Figure() {
    red=1;
    blue=1;
    green=1;
    filename="";
}

Figure::Figure(const Figure& fig) {
    red = fig.red;
    green = fig.green;
    blue = fig.blue;
    filename = fig.filename;
}

Figure::Figure(float redG,float greenG,float blueG,std::string filenameG) {
    red=redG;
    green=greenG;
    blue=blueG;
    filename=filenameG;
}