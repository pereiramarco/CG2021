#include "../include/Sphere.h"
#include "../include/Model.h"
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
    Ponto3D *top=new Ponto3D(0.0f,radius,0.0f),*bottom=new Ponto3D(0.0f,-radius,0.0f);
    static int special=1;
    Triangulo *t;
    pair<int,int> point_before(slice-last,stack);
    pair<int,int> point_now(slice*last+(1-last),stack);
    Ponto3D *second=points[point_before];
    Ponto3D *third=points[point_now]; 
    if (onTop)
        t = new Triangulo(top,second,third,new Ponto3D(special,1.0f,0.0f));
    else 
        t = new Triangulo(bottom,third,second,new Ponto3D(special,1-special,0.0f));
    this->faces.push_back(t);
    special=1-special;
}

void Sphere::addLastSlice(int last,int slice,int stack) {//last=0 se for última, last=1 caso contrário;
    pair<int,int> topleft(slice-last,stack-1),topright(slice*last+(1-last),stack-1),bottomleft(slice-last,stack),bottomright(slice*last+(1-last),stack);
    Ponto3D * topRight=points[topright],*topLeft=points[topleft],*bottomLeft=points[bottomleft],*bottomRight=points[bottomright];
    Triangulo *t1=new Triangulo(topRight,topLeft,bottomLeft,new Ponto3D(0.0f,0.0f,1.0f));
    Triangulo *t2=new Triangulo(topRight,bottomLeft,bottomRight,new Ponto3D(1.0f,0.0f,0.0f));
    faces.push_back(t1);
    faces.push_back(t2);
}

Model Sphere::generate() {
    double slice_angle_increment=M_PI/nSlices;
    double stack_angle_increment=M_PI/(nStacks+1);
    for (int stack=1;stack<=nStacks;stack++) {

        double stack_angle=stack*stack_angle_increment;
        float y=radius*cosf(stack_angle);
        bool first=true;

        for (int slice=1;slice<=2*nSlices;slice++) {

            double slice_angle=slice*slice_angle_increment;
            float hypotenuse=radius*sinf(stack_angle);
            float x=hypotenuse*cosf(slice_angle);
            float z=-hypotenuse*sinf(slice_angle);

            Ponto3D * ponto=new Ponto3D(x,y,z);

            //addPoint
            pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;
            if (first) {first=false;continue;} //primeira iteração de cada slice deve apenas guardar o ponto
            if (stack==1) {//forma triangulos
                addTopOrBottom(true,slice,stack,1);
                if (slice==2*nSlices)
                    addTopOrBottom(true,slice,stack,0);
            }
            else {//forma quadrados
                addLastSlice(1,slice,stack);
                if (slice==2*nSlices) //une quando está na última slice
                    addLastSlice(0,slice,stack);
            }
            if (stack==nStacks) {
                addTopOrBottom(false,slice,stack,1);
                if (slice==2*nSlices)
                    addTopOrBottom(false,slice,stack,0);
            }
        }
    }
    return Model();
}

void Sphere::saveToFile(string filename){
    ofstream fout(filename, ios::out) ; 
    fout<< "sphere\n" << to_string(nSlices) << "\n" << to_string(nStacks) << "\n" << to_string(radius) << "\n";
    for (int i=1;i<=2*nSlices;i++) {
        for (int j=1;j<=nStacks;j++) {
            Ponto3D* p = points[pair<int,int>(i,j)];
            fout<< to_string(i) << " " << to_string(j) << " " << to_string(p->x) << " " << to_string(p->y) << " " << to_string(p->z) << "\n";
        }
    }
}

void Sphere::draw() {
    for (auto& t : faces) {
        t->desenha();
    }
}