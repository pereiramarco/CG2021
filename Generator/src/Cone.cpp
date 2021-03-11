#include "../include/Cone.h"
#include "../../Utils/Point3D.h"
#include "../include/Model.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

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
    Point3D *top=new Point3D(0.0f,height,0.0f,1);
    static int special=1;
    Triangle *t;
    pair<int,int> point_before(slice-not_last,stack);
    pair<int,int> point_after(slice*not_last+(1-not_last),stack);
    Point3D *before=points[point_before];
    Point3D *after=points[point_after]; 
    t = new Triangle(top,before,after);
    this->faces.push_back(t);
    special=1-special;
}
void Cone::addCircleSlice(int slice,int stack,int not_last) {
    Point3D * middle=new Point3D();
    pair<int,int> before(slice-not_last,stack),after(slice*not_last+(1-not_last),stack);
    Point3D* afterPoint=points[after],*beforePoint=points[before];
    Triangle *t=new Triangle(middle,afterPoint,beforePoint); //é visto debaixo logo está mudada a ordem
    faces.push_back(t);
}

void Cone::addSquareSlice(int slice,int stack,int not_last) {
    pair<int,int> bottomleft(slice-not_last,stack-1),bottomright(slice*not_last+(1-not_last),stack-1),topleft(slice-not_last,stack),topright(slice*not_last+(1-not_last),stack);
    Point3D * topRight=points[topright],*topLeft=points[topleft],*bottomLeft=points[bottomleft],*bottomRight=points[bottomright];
    Triangle *t1=new Triangle(topRight,topLeft,bottomLeft);
    Triangle *t2=new Triangle(topRight,bottomLeft,bottomRight);
    faces.push_back(t1);
    faces.push_back(t2);
}

Model* Cone::generate() {
    bool first;
    double slice_angle_increment=M_PI*2.0/nSlices;
    double height_increment=height/(1.0*(nStacks+1));
    vector<Point3D*> vertixes;
    int index=2;
    Point3D *top=new Point3D(0.0f,height,0.0f,1);
    vertixes.push_back(new Point3D());
    vertixes.push_back(top);

    for (int stack=0;stack<=nStacks;stack++) {
        float y=height_increment*stack;
        float stackRadius=((height-y)*radiusBase)/height;
        first=true;

        for (int slice=1;slice<=nSlices;slice++) {
            float x=cos(slice_angle_increment*slice)*stackRadius;
            float z=-sinf(slice_angle_increment*slice)*stackRadius;

            Point3D * ponto = new Point3D(x,y,z,index++);
            vertixes.push_back(ponto);
            pair<int,int> sliceAndStack(slice,stack);
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
            if (stack==nStacks) {
                addTopSlice(slice,stack,1);
                if (slice==nSlices) {
                    addTopSlice(slice,stack,0);
                }
            }
        }
    }
    return new Model(vertixes,faces);
}