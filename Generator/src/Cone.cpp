#include "../include/Cone.h"
#include "../../Utils/Point3D.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>

Cone::Cone() {
    radiusBase=1;
    nStacks=10;
    nSlices=10;
    height=2;
}

Cone::Cone(int radiusG,int heightG,int slicesG,int stacksG) {
    radiusBase=radiusG;
    nStacks=stacksG;
    nSlices=slicesG;
    height=heightG;
}


void Cone::addTopSlice(int slice,int stack,int not_last) {
    std::shared_ptr<Point3D> top=std::make_shared<Point3D>(0.0f,height,0.0f,1);
    static int special=1;
    std::shared_ptr<Triangle> t;
    std::pair<int,int> point_before(slice-not_last,stack);
    std::pair<int,int> point_after(slice*not_last+(1-not_last),stack);
    std::shared_ptr<Point3D> before=points[point_before];
    std::shared_ptr<Point3D> after=points[point_after]; 
    t =std::make_shared<Triangle>(top,before,after);
    this->faces.push_back(t);
    special=1-special;
}
void Cone::addCircleSlice(int slice,int stack,int not_last) {
    std::shared_ptr<Point3D> middle=std::make_shared<Point3D>();
    std::pair<int,int> before(slice-not_last,stack),after(slice*not_last+(1-not_last),stack);
    std::shared_ptr<Point3D> afterPoint=points[after],beforePoint=points[before];
    std::shared_ptr<Triangle> t=std::make_shared<Triangle>(middle,afterPoint,beforePoint); //é visto debaixo logo está mudada a ordem
    faces.push_back(t);
}

void Cone::addSquareSlice(int slice,int stack,int not_last) {
    std::pair<int,int> bottomleft(slice-not_last,stack-1),bottomright(slice*not_last+(1-not_last),stack-1),topleft(slice-not_last,stack),topright(slice*not_last+(1-not_last),stack);
    std::shared_ptr<Point3D> topRight=points[topright],topLeft=points[topleft],bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    std::shared_ptr<Triangle> t1=std::make_shared<Triangle>(topRight,topLeft,bottomLeft);
    std::shared_ptr<Triangle> t2=std::make_shared<Triangle>(topRight,bottomLeft,bottomRight);
    faces.push_back(t1);
    faces.push_back(t2);
}

std::shared_ptr<Model> Cone::generate() {
    bool first;
    double slice_angle_increment=M_PI*2.0/nSlices;
    double height_increment=height/(1.0*nStacks);
    std::vector<std::shared_ptr<Point3D>> vertixes;
    int index=2;
    std::shared_ptr<Point3D> top=std::make_shared<Point3D>(0.0f,height,0.0f,1);
    vertixes.push_back(std::make_shared<Point3D>());
    vertixes.push_back(top);

    for (int stack=0;stack<nStacks;stack++) {
        float y=height_increment*stack;
        float stackRadius=((height-y)*radiusBase)/height;
        first=true;

        for (int slice=1;slice<=nSlices;slice++) {
            float x=cos(slice_angle_increment*slice)*stackRadius;
            float z=-sinf(slice_angle_increment*slice)*stackRadius;

            std::shared_ptr<Point3D> ponto =std::make_shared<Point3D>(x,y,z,index++);
            vertixes.push_back(ponto);
            std::pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;

            if (first) {first=false;continue;}
            if (stack==0) {
                addCircleSlice(slice,stack,1);
                if (slice==nSlices) {
                    addCircleSlice(slice,stack,0);
                }
            }
            else {
                addSquareSlice(slice,stack,1);
                if (slice==nSlices) {
                    addSquareSlice(slice,stack,0);
                }
            }
            if (stack==nStacks-1) {
                addTopSlice(slice,stack,1);
                if (slice==nSlices) {
                    addTopSlice(slice,stack,0);
                }
            }
        }
    }
    return std::make_shared<Model>(vertixes,faces);
}