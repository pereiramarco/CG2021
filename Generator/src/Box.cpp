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
}

Box::Box(int widthG,int depthG,int heightG,int nDivisionsG) {
    width=widthG;
    depth=depthG;
    height=heightG;
    nDivisions=nDivisionsG;
}

void Box::addSquare(bool top,std::shared_ptr<Point3D> topRight,std::shared_ptr<Point3D> topLeft,std::shared_ptr<Point3D> bellowLeft,std::shared_ptr<Point3D> bellowRight) {
    std::shared_ptr<Triangle>t1,t2;
    if (top) {
        t1=std::make_shared<Triangle>(topRight,topLeft,bellowLeft);
        t2=std::make_shared<Triangle>(topRight,bellowLeft,bellowRight);
    }
    else {
        t1=std::make_shared<Triangle>(topRight,bellowLeft,topLeft);
        t2=std::make_shared<Triangle>(topRight,bellowRight,bellowLeft);
    }
    faces.push_back(t1);
    faces.push_back(t2);
}

void Box::addYLayer(bool top) { 
    int y=top?nDivisions:0;
    for (int x=0;x<nDivisions;x++) {
        for (int z=0;z<nDivisions;z++) {
            std::shared_ptr<Point3D> topLeft=points[std::tuple<int,int,int>(x,y,z)];
            std::shared_ptr<Point3D> topRight=points[std::tuple<int,int,int>(x+1,y,z)];
            std::shared_ptr<Point3D> bellowLeft=points[std::tuple<int,int,int>(x,y,z+1)];
            std::shared_ptr<Point3D> bellowRight=points[std::tuple<int,int,int>(x+1,y,z+1)];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addXLayer(bool top) {
    int x=top?nDivisions:0;
    for (int y=0;y<nDivisions;y++) {
        for (int z=0;z<nDivisions;z++) {
            std::shared_ptr<Point3D> topLeft=points[std::tuple<int,int,int>(x,y,z)];
            std::shared_ptr<Point3D> topRight=points[std::tuple<int,int,int>(x,y,z+1)];
            std::shared_ptr<Point3D> bellowLeft=points[std::tuple<int,int,int>(x,y+1,z)];
            std::shared_ptr<Point3D> bellowRight=points[std::tuple<int,int,int>(x,y+1,z+1)];
            addSquare(top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

void Box::addZLayer(bool top) {
    int z=top?nDivisions:0;
    for (int x=0;x<nDivisions;x++) {
        for (int y=0;y<nDivisions;y++) {
            std::shared_ptr<Point3D> topLeft=points[std::tuple<int,int,int>(x,y,z)];
            std::shared_ptr<Point3D> topRight=points[std::tuple<int,int,int>(x+1,y,z)];
            std::shared_ptr<Point3D> bellowLeft=points[std::tuple<int,int,int>(x,y+1,z)];
            std::shared_ptr<Point3D> bellowRight=points[std::tuple<int,int,int>(x+1,y+1,z)];
            addSquare(!top,topRight,topLeft,bellowLeft,bellowRight);
        }
    }
}

std::shared_ptr<Model> Box::generate() {
    float x_increment=1.0*width/(1.0*nDivisions);
    float y_increment=1.0*height/(1.0*nDivisions);
    float z_increment=1.0*depth/(1.0*nDivisions);
    int index=0;
    std::vector<std::shared_ptr<Point3D>> vertixes;
    for (int y=0;y<=nDivisions;y++) {
        for (int x=0;x<=nDivisions;x++) {
            for (int z=0;z<=nDivisions;z++) {
                if (y==0 || y==nDivisions || x==0 || x==nDivisions || z==0 || z==nDivisions) { 
                    std::shared_ptr<Point3D> p = std::make_shared<Point3D>(x*x_increment,y*y_increment,z*z_increment,index++);
                    vertixes.push_back(p);
                    std::tuple<int,int,int> t(x,y,z);
                    points[t]=p;
                }
            }
        }
    }
    addYLayer(false);
    addYLayer(true);
    addXLayer(false);
    addXLayer(true);
    addZLayer(false);
    addZLayer(true);
    return std::make_shared<Model>(vertixes,faces);
}