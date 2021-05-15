#include "../include/Sphere.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include "../include/Model.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>

Sphere::Sphere() {
    radius=1;
    nStacks=10;
    nSlices=10;
}

Sphere::Sphere(int radiusG,int slicesG,int stacksG) {
    radius=radiusG;
    nStacks=stacksG;
    nSlices=slicesG;
}

void Sphere::addTopOrBottomSlice(bool onTop,int slice,int stack,int last) { //last será um se for última slice e 1 caso contrário
    Point3D top=Point3D(0.0f,radius,0.0f,0),bottom=Point3D(0.0f,-radius,0.0f,1);
    Triangle t;
    std::pair<int,int> point_before(slice-last,stack);
    std::pair<int,int> point_now(slice*last+(1-last),stack);
    Point3D second=points[point_before];
    Point3D third=points[point_now]; 
    if (onTop)
        t = Triangle(top.index,second.index,third.index);
    else 
        t = Triangle(bottom.index,third.index,second.index);
    this->faces.push_back(t);
}

void Sphere::addSquareSlice(int slice,int stack,int not_last) {//last=0 se for última, last=1 caso contrário;
    std::pair<int,int> topleft(slice-not_last,stack-1),topright(slice*not_last+(1-not_last),stack-1);
    std::pair<int,int> bottomleft(slice-not_last,stack),bottomright(slice*not_last+(1-not_last),stack);
    Point3D topRight=points[topright],topLeft=points[topleft];
    Point3D bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    Triangle t1=Triangle(topRight.index,topLeft.index,bottomLeft.index);
    Triangle t2=Triangle(topRight.index,bottomLeft.index,bottomRight.index);
    faces.push_back(t1);
    faces.push_back(t2);
}

std::shared_ptr<Model> Sphere::generate() {
    double slice_angle_increment=M_PI*2.0/nSlices;
    double stack_angle_increment=M_PI/nStacks;
    int index=2;
    std::vector<Point3D> vertixes;
    Point3D top=Point3D(0.0f,radius,0.0f,0),bottom=Point3D(0.0f,-radius,0.0f,1);
    vertixes.push_back(top);
    vertixes.push_back(bottom);
    normals.push_back(Point3D(0.0f,1.0f,0.0f));
    normals.push_back(Point3D(0.0f,-1.0f,0.0f));
    for (int stack=1;stack<nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        float y=radius*cosf(stack_angle);
        float stackRadius=radius*sinf(stack_angle);
        bool first=true;

        for (int slice=1;slice<=nSlices;slice++) {

            double slice_angle=slice*slice_angle_increment;
            float x=stackRadius*cosf(slice_angle);
            float z=-stackRadius*sinf(slice_angle);

            Point3D ponto=Point3D(x,y,z,index++);
            vertixes.push_back(ponto);
            Point3D normal=Point3D(x,y,z);
            normal.normalize();
            normals.push_back(normal);

            //addPoint
            std::pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;
            if (first) {first=false;continue;} //primeira iteração de cada slice deve apenas guardar o ponto
            if (stack==1) {//forma triangulos
                addTopOrBottomSlice(true,slice,stack,1);
                if (slice==nSlices)
                    addTopOrBottomSlice(true,slice,stack,0);
            }
            else {//forma quadrados
                addSquareSlice(slice,stack,1);
                if (slice==nSlices) //une quando está na última slice
                    addSquareSlice(slice,stack,0);
            }
            if (stack==nStacks-1) {
                addTopOrBottomSlice(false,slice,stack,1);
                if (slice==nSlices)
                    addTopOrBottomSlice(false,slice,stack,0);
            }
        }
    }
    return std::make_shared<Model>(vertixes,faces,normals);
}

