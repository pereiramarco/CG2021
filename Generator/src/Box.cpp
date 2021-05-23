#include "../include/Box.h"
#include "../../Utils/Point3D.h"
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

Box::Box() {
    nDivisions=0;
    width=10;
    depth=10;
    height=10;
    index=0;
}

Box::Box(int widthG,int depthG,int heightG,int nDivisionsG) {
    width=widthG;
    depth=depthG;
    height=heightG;
    nDivisions=nDivisionsG;
    index=0;
}

void Box::addSquare(bool top,Point3D topRight,Point3D topLeft,Point3D bellowLeft,Point3D bellowRight) {
    Triangle t1,t2;
    if (top) {
        t1=Triangle(topRight.index,topLeft.index,bellowLeft.index);
        t2=Triangle(topRight.index,bellowLeft.index,bellowRight.index);
    }
    else {
        t1=Triangle(topRight.index,bellowLeft.index,topLeft.index);
        t2=Triangle(topRight.index,bellowRight.index,bellowLeft.index);
    }
    faces.push_back(t1);
    faces.push_back(t2);
}

void Box::addYLayer(bool top) { 
    float x_increment=1.0*width/(1.0*nDivisions);
    float z_increment=1.0*depth/(1.0*nDivisions);
    float tex_increment = 1.0/(1.0*nDivisions);
    int y=top?1:0;
    std::vector<Point3D> layer;
    for(int x=0;x<=nDivisions;x++) {
        for(int z=0;z<=nDivisions;z++) {
            layer.push_back(Point3D(x*x_increment,y*height,z*z_increment,index++));
            texCoords.push_back(std::make_pair<float,float>(x*tex_increment,z*tex_increment));
        }
    }
    for(int x=0;x<nDivisions;x++) {
        for(int z=0;z<nDivisions;z++) {
            Point3D topLeft=layer[((nDivisions+1)*x)+z];
            Point3D topRight=layer[((nDivisions+1)*(x+1))+z];
            Point3D bellowLeft=layer[((nDivisions+1)*x)+z+1];
            Point3D bellowRight=layer[((nDivisions+1)*(x+1))+z+1];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(int i = 0; i < layer.size(); i++)
        normals.push_back(Point3D(0,top?1:-1,0));
    points.insert(points.end(),layer.begin(),layer.end());
}

void Box::addXLayer(bool top) {
    float y_increment=1.0*height/(1.0*nDivisions);
    float z_increment=1.0*depth/(1.0*nDivisions);
    float tex_increment = 1.0/(1.0*nDivisions);
    int x=top?1:0;
    std::vector<Point3D> layer;
    for(int y=0;y<=nDivisions;y++) {
        for(int z=0;z<=nDivisions;z++) {
            layer.push_back(Point3D(x*width,y*y_increment,z*z_increment,index++));
            texCoords.push_back(std::make_pair<float,float>(z*tex_increment,y*tex_increment));
        }
    }
    for(int y=0;y<nDivisions;y++) {
        for(int z=0;z<nDivisions;z++) {
            Point3D topLeft=layer[((nDivisions+1)*y)+z];
            Point3D topRight=layer[((nDivisions+1)*y)+z+1];
            Point3D bellowLeft=layer[((nDivisions+1)*(y+1))+z];
            Point3D bellowRight=layer[((nDivisions+1)*(y+1))+z+1];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(int i = 0; i < layer.size(); i++)
        normals.push_back(Point3D(top?1:-1,0,0));
    points.insert(points.end(),layer.begin(),layer.end());
}

void Box::addZLayer(bool top) {
    float y_increment=1.0*height/(1.0*nDivisions);
    float x_increment=1.0*width/(1.0*nDivisions);
    float tex_increment = 1.0/(1.0*nDivisions);
    int z=top?1:0;
    std::vector<Point3D> layer;
    for(int y=0;y<=nDivisions;y++) {
        for(int x=0;x<=nDivisions;x++) {
            layer.push_back(Point3D(x*x_increment,y*y_increment,z*depth,index++));
            texCoords.push_back(std::make_pair<float,float>(x*tex_increment,y*tex_increment));
        }
    }
    for(int y=0;y<nDivisions;y++) {
        for(int x=0;x<nDivisions;x++) {
            Point3D bellowLeft=layer[((nDivisions+1)*y)+x];
            Point3D bellowRight=layer[((nDivisions+1)*y)+x+1];
            Point3D topLeft=layer[((nDivisions+1)*(y+1))+x];
            Point3D topRight=layer[((nDivisions+1)*(y+1))+x+1];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
    for(int i = 0; i < layer.size(); i++)
        normals.push_back(Point3D(0,0,top?1:-1));
    points.insert(points.end(),layer.begin(),layer.end());
}

std::shared_ptr<Model> Box::generate() {
    addYLayer(false);
    addYLayer(true);
    addXLayer(false);
    addXLayer(true);
    addZLayer(false);
    addZLayer(true);
    return std::make_shared<Model>(points,faces,normals,texCoords);
}
