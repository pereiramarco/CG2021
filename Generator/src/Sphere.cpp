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

void Sphere::addTopOrBottomSlice(bool onTop,int slice,int stack) {
    Point3D top=vertexes[2*(slice-1)],bottom=vertexes[(2*(slice-1))+1];
    Triangle t;
    std::pair<int,int> point_before(slice-1,stack);
    std::pair<int,int> point_now(slice,stack);
    Point3D second=points[point_before];
    Point3D third=points[point_now]; 
    if (onTop)
        t = Triangle(top.index,second.index,third.index);
    else 
        t = Triangle(bottom.index,third.index,second.index);
    this->faces.push_back(t);
}

void Sphere::addSquareSlice(int slice,int stack) {
    std::pair<int,int> topleft(slice-1,stack-1),topright(slice,stack-1);
    std::pair<int,int> bottomleft(slice-1,stack),bottomright(slice,stack);
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
    float tex_x_increment = 1.0/(1.0*nSlices);
    float tex_y_increment = 1.0/(1.0*nStacks);
    int index=0;
    for(int i = 0; i < nSlices; i++) {
        Point3D top=Point3D(0.0f,radius,0.0f,index++);
        Point3D bottom=Point3D(0.0f,-radius,0.0f,index++);
        vertexes.push_back(top);
        vertexes.push_back(bottom);
        normals.push_back(Point3D(0.0f,1.0f,0.0f));
        normals.push_back(Point3D(0.0f,-1.0f,0.0f));
        double x_tex_coord = i * tex_x_increment * 1.0 + (tex_x_increment / 2.0);
        texCoords.push_back(std::make_pair<float,float>(x_tex_coord,1.0));
        texCoords.push_back(std::make_pair<float,float>(x_tex_coord,0.0));
    }
    for (int stack=1;stack<nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        float y=radius*cosf(stack_angle);
        float stackRadius=radius*sinf(stack_angle);
        bool first=true;

        for (int slice=0;slice<=nSlices;slice++) {

            double slice_angle=slice*slice_angle_increment;
            float x=stackRadius*cosf(slice_angle);
            float z=-stackRadius*sinf(slice_angle);

            Point3D ponto=Point3D(x,y,z,index++);
            vertexes.push_back(ponto);
            Point3D normal=Point3D(x,y,z);
            normal.normalize();
            normals.push_back(normal);
            texCoords.push_back(std::make_pair<float,float>(slice*tex_x_increment,(nStacks-stack)*tex_y_increment));

            //addPoint
            std::pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;
            if (first) {first=false;continue;} //primeira iteração de cada slice deve apenas guardar o ponto
            if (stack==1) {//forma triangulos
                addTopOrBottomSlice(true,slice,stack);
            }
            else {//forma quadrados
                addSquareSlice(slice,stack);
            }
            if (stack==nStacks-1) {
                addTopOrBottomSlice(false,slice,stack);
            }
        }
    }
    return std::make_shared<Model>(vertexes,faces,normals,texCoords);
}

