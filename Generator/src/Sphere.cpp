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
    std::shared_ptr<Point3D> top=std::make_shared<Point3D>(0.0f,radius,0.0f,0),bottom=std::make_shared<Point3D>(0.0f,-radius,0.0f,1);
    std::shared_ptr<Triangle> t;
    std::pair<int,int> point_before(slice-last,stack);
    std::pair<int,int> point_now(slice*last+(1-last),stack);
    std::shared_ptr<Point3D> second=points[point_before];
    std::shared_ptr<Point3D> third=points[point_now]; 
    if (onTop)
        t = std::make_shared<Triangle>(top,second,third);
    else 
        t = std::make_shared<Triangle>(bottom,third,second);
    this->faces.push_back(t);
}

void Sphere::addSquareSlice(int slice,int stack,int not_last) {//last=0 se for última, last=1 caso contrário;
    std::pair<int,int> topleft(slice-not_last,stack-1),topright(slice*not_last+(1-not_last),stack-1);
    std::pair<int,int> bottomleft(slice-not_last,stack),bottomright(slice*not_last+(1-not_last),stack);
    std::shared_ptr<Point3D> topRight=points[topright],topLeft=points[topleft];
    std::shared_ptr<Point3D> bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    std::shared_ptr<Triangle> t1=std::make_shared<Triangle>(topRight,topLeft,bottomLeft);
    std::shared_ptr<Triangle> t2=std::make_shared<Triangle>(topRight,bottomLeft,bottomRight);
    faces.push_back(t1);
    faces.push_back(t2);
}

std::shared_ptr<Model> Sphere::generate() {
    double slice_angle_increment=M_PI*2.0/nSlices;
    double stack_angle_increment=M_PI/nStacks;
    int index=2;
    std::vector<std::shared_ptr<Point3D>> vertixes;
    std::shared_ptr<Point3D> top=std::make_shared<Point3D>(0.0f,radius,0.0f,0),bottom=std::make_shared<Point3D>(0.0f,-radius,0.0f,1);
    vertixes.push_back(top);
    vertixes.push_back(bottom);
    for (int stack=1;stack<nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        float y=radius*cosf(stack_angle);
        float stackRadius=radius*sinf(stack_angle);
        bool first=true;

        for (int slice=1;slice<=nSlices;slice++) {

            double slice_angle=slice*slice_angle_increment;
            float x=stackRadius*cosf(slice_angle);
            float z=-stackRadius*sinf(slice_angle);

            std::shared_ptr<Point3D> ponto=std::make_shared<Point3D>(x,y,z,index++);
            vertixes.push_back(ponto);

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
    return std::make_shared<Model>(vertixes,faces);
}

