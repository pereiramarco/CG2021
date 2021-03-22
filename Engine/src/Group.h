#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <unordered_set>

enum Transformation {RotateType,TranslateType,ScaleType};

class Transform {
public:    
     Transformation type;

     virtual std::string toString()=0;
     virtual void applyTransform()=0;
};

class Rotation : public Transform {
public:    
    float degrees;
    float axisX;
    float axisY;
    float axisZ;

    Rotation(Transformation typeG,float degreesG, float axisXG, float axisYG, float axisZG) {
        type=typeG;
        degrees=degreesG;
        axisX=axisXG;
        axisY=axisYG;
        axisZ=axisZG;
    }

    std::string toString() {
        std::string axisx = std::to_string(axisX);
        std::string axisy = std::to_string(axisY);
        std::string axisz = std::to_string(axisZ);
        return axisx + " " + axisy + " " + axisz;
    }

    void applyTransform() {
        glRotatef(degrees,axisX,axisY,axisZ);
    }

};

class Translation : public Transform {
public:
    float x;
    float y;
    float z;

    Translation(Transformation typeG,float xG, float yG, float zG) {
        type=typeG;
        x=xG;
        y=yG;
        z=zG;
    } 

    std::string toString() {
        std::string xx = std::to_string(x);
        std::string yy = std::to_string(y);
        std::string zz = std::to_string(z);
        return xx + " " + yy + " " + zz;
    }

    void applyTransform() {
        glTranslatef(x,y,z);
    }

};

class Scale : public Transform {
public:
    float xScale;
    float yScale;
    float zScale;

    Scale(Transformation typeG,float xG, float yG, float zG) {
        type=typeG;
        xScale=xG;
        yScale=yG;
        zScale=zG;
    } 

    std::string toString() {
        std::string xscale = std::to_string(xScale);
        std::string yscale = std::to_string(yScale);
        std::string zscale = std::to_string(zScale);
        return xscale + " " + yscale + " " + zscale;
    }

    void applyTransform() {
        glScalef(xScale,yScale,zScale);
    }

};

class Group {
public:
    std::vector<Transform*> transformations;
    std::vector<std::string> files;
    std::vector<Group*> nestedGroups;

    Group() {}

    void addTransform(Transform * t);

    void addFile(std::string filename);

    void addGroup(Group * group);

    void print(int ident_number);

    std::unordered_set<std::string> getModels();

private:
    void ident(int identNumber);
};