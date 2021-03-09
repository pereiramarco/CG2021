#include "../include/Sphere.h"
#include <vector>
#include "../../Utils/Ponto3D.h"
#include "../include/Model.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
#include <fstream>

using namespace std;

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

void Sphere::addTopOrBottom(bool onTop,int slice,int stack,int last) { //last será um se for última slice e 1 caso contrário
    Ponto3D *top=new Ponto3D(0.0f,radius,0.0f,0),*bottom=new Ponto3D(0.0f,-radius,0.0f,1);
    static int special=1;
    Triangulo *t;
    pair<int,int> point_before(slice-last,stack);
    pair<int,int> point_now(slice*last+(1-last),stack);
    Ponto3D *second=points[point_before];
    Ponto3D *third=points[point_now]; 
    if (onTop)
        t = new Triangulo(top,second,third);
    else 
        t = new Triangulo(bottom,third,second);
    this->faces.push_back(t);
    special=1-special;
}

void Sphere::addSlice(int last,int slice,int stack) {//last=0 se for última, last=1 caso contrário;
    pair<int,int> topleft(slice-last,stack-1),topright(slice*last+(1-last),stack-1);
    pair<int,int> bottomleft(slice-last,stack),bottomright(slice*last+(1-last),stack);
    Ponto3D * topRight=points[topright],*topLeft=points[topleft];
    Ponto3D *bottomLeft=points[bottomleft],*bottomRight=points[bottomright];
    Triangulo *t1=new Triangulo(topRight,topLeft,bottomLeft);
    Triangulo *t2=new Triangulo(topRight,bottomLeft,bottomRight);
    faces.push_back(t1);
    faces.push_back(t2);
}

Model* Sphere::generate() {
    double slice_angle_increment=M_PI*2.0/nSlices;
    double stack_angle_increment=M_PI/(nStacks+1);
    int index=2;
    vector<Ponto3D*> vertixes;
    Ponto3D *top=new Ponto3D(0.0f,radius,0.0f,0),*bottom=new Ponto3D(0.0f,-radius,0.0f,1);
    vertixes.push_back(top);
    vertixes.push_back(bottom);
    for (int stack=1;stack<=nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        float y=radius*cosf(stack_angle);
        float hypotenuse=radius*sinf(stack_angle);
        bool first=true;

        for (int slice=1;slice<=nSlices;slice++) {

            double slice_angle=slice*slice_angle_increment;
            float x=hypotenuse*cosf(slice_angle);
            float z=-hypotenuse*sinf(slice_angle);

            Ponto3D * ponto=new Ponto3D(x,y,z,index++);
            vertixes.push_back(ponto);

            //addPoint
            pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;
            if (first) {first=false;continue;} //primeira iteração de cada slice deve apenas guardar o ponto
            if (stack==1) {//forma triangulos
                addTopOrBottom(true,slice,stack,1);
                if (slice==nSlices)
                    addTopOrBottom(true,slice,stack,0);
            }
            else {//forma quadrados
                addSlice(1,slice,stack);
                if (slice==nSlices) //une quando está na última slice
                    addSlice(0,slice,stack);
            }
            if (stack==nStacks) {
                addTopOrBottom(false,slice,stack,1);
                if (slice==nSlices)
                    addTopOrBottom(false,slice,stack,0);
            }
        }
    }
    return new Model(vertixes,faces);
}

