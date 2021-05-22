#include "../include/Figure.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

Figure::Figure() {
    diffR=diffG=diffB=1;
    emissR=-1;
    specR=-1;
    ambR=-1;
    shininess=-1;
    filename="";
    texID = 0;
}

Figure::Figure(const Figure& fig) {
    diffR = fig.diffR;diffG = fig.diffG;diffB = fig.diffB;
    specR = fig.specR;specG = fig.specG;specB = fig.specB;
    emissR = fig.emissR;emissG = fig.emissG;emissB = fig.emissB;
    ambR = fig.ambR;ambG = fig.ambG;ambB = fig.ambB;
    shininess = fig.shininess;
    filename = fig.filename;
    texID = fig.texID;
}

// Point3D maps x,y,z to R,G,B

Figure::Figure(int textureG, Point3D diff,Point3D spec,float shin,Point3D amb, Point3D emiss,std::string filenameG) {
    diffR = diff.x;diffG = diff.y;diffB = diff.z;
    emissR= emiss.x;emissG = emiss.y;emissB = emiss.z;
    specR = spec.x;specG = spec.y;specB = spec.z;
    ambR = amb.x;ambG = amb.y;ambB = amb.z;
    shininess=shin;
    filename=filenameG;
    texID = textureG;
}

void Figure::apply() {
    if(diffR != -1 && diffG != -1 && diffB != -1) {
        float appdiff[4] = {diffR,diffG,diffB,1.0};
        glMaterialfv(GL_FRONT,GL_DIFFUSE,appdiff);
    }
    if(emissR != -1 && emissG != -1 && emissB != -1) {
        float appemiss[4] = {emissR,emissG,emissB,1.0};
        glMaterialfv(GL_FRONT,GL_EMISSION,appemiss);
    }
    if(specR != -1 && specG != -1 && specB != -1) {
        float appspec[4] = {specR,specG,specB,1.0};
        glMaterialfv(GL_FRONT,GL_SPECULAR,appspec);
    }
    if(shininess != -1)
        glMaterialf(GL_FRONT,GL_SHININESS,shininess);
    if(ambR != -1 && ambG != -1 && ambB != -1) {
        float appamb[4] = {ambR,ambG,ambB,1.0};
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,appamb);
    }
    if(texID != 0)
        glBindTexture(GL_TEXTURE_2D,texID);
}

void Figure::reset() {
    float defamb[4] = {0.2,0.2,0.2,1.0};
    float defdiff[4] = {0.8,0.8,0.8,1.0};
    float defemiss[4] = {0.0,0.0,0.0,1.0};
    float defspec[4] = {0.0,0.0,0.0,1.0};
    float defshin = 0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,defamb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,defdiff);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,defemiss);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,defspec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,defshin);
    glBindTexture(GL_TEXTURE_2D,0);
}
