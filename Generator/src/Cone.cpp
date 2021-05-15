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
    Point3D top=Point3D(0.0f,height,0.0f,1);
    static int special=1;
    Triangle t;
    std::pair<int,int> point_before(slice-not_last,stack);
    std::pair<int,int> point_after(slice*not_last+(1-not_last),stack);
    Point3D before=points[point_before];
    Point3D after=points[point_after]; 
    t = Triangle(top.index,before.index,after.index);
    this->faces.push_back(t);
    special=1-special;
}

void Cone::addCircleSlice(int slice,int stack,int not_last) {
    Point3D middle=Point3D();
    std::pair<int,int> before(slice-not_last,stack),after(slice*not_last+(1-not_last),stack);
    Point3D afterPoint=points[after],beforePoint=points[before];
    Triangle t=Triangle(middle.index,afterPoint.index,beforePoint.index); //é visto debaixo logo está mudada a ordem
    faces.push_back(t);
}

void Cone::addSquareSlice(int slice,int stack,int not_last) {
    std::pair<int,int> bottomleft(slice-not_last,stack),bottomright(slice*not_last+(1-not_last),stack),topleft(slice-not_last,stack+1),topright(slice*not_last+(1-not_last),stack+1);
    Point3D topRight=points[topright],topLeft=points[topleft],bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    Triangle t1=Triangle(topRight.index,topLeft.index,bottomLeft.index);
    Triangle t2=Triangle(topRight.index,bottomLeft.index,bottomRight.index);
    faces.push_back(t1);
    faces.push_back(t2);
}


void Cone::addBase(int index) {
    double slice_angle_increment=M_PI*2.0/nSlices;
    std::vector<Point3D> points;
    for(int slice = 0; slice < nSlices; slice++) {
        float x=cos(slice_angle_increment*slice)*radiusBase;
        float z=-sinf(slice_angle_increment*slice)*radiusBase;
        Point3D ponto =Point3D(x,0,z,index++);
        points.push_back(ponto);
        normals.push_back(Point3D(0.0f,-1.0f,0.0f));
        if(slice==0)
            continue;
        Point3D beforePoint = points[slice-1];
        Triangle t = Triangle(0,index-1,index-2); // Ordem: Ponto centro(indice 0) -> ponto atual(indice index-1) -> ponto anterior(indiec index-1-1)
        faces.push_back(t);
    }
    Triangle t = Triangle(0,points[0].index,index-1); // Adicionar o último triângulo
    faces.push_back(t);
    vertexes.insert(vertexes.end(),points.begin(),points.end());
}

void Cone::computeNormals(int stack) {
    for(int i = 1; i <= nSlices; i++) {
        std::pair<int,int> beforepoint((i-1==0?nSlices:i-1),stack);
        std::pair<int,int> afterpoint((i==nSlices?1:i+1),stack);
        std::pair<int,int> actualpoint(i,stack);
        Point3D topPoint;
        if(stack != nStacks-1) {
            std::pair<int,int> toppoint(i,stack+1);
            topPoint=points[toppoint];
        }
        else
            topPoint = Point3D(0.0f,height,0.0f,1);
        Point3D beforePoint=points[beforepoint];
        Point3D afterPoint=points[afterpoint];
        Point3D actualPoint=points[actualpoint];
        Point3D horizontalVector(afterPoint.x-beforePoint.x,afterPoint.y-beforePoint.y,afterPoint.z-beforePoint.z);
        Point3D verticalVector(topPoint.x-actualPoint.x,topPoint.y-actualPoint.y,topPoint.z-actualPoint.z);
        Point3D normalVector = horizontalVector.crossProduct(verticalVector);
        normalVector.normalize();
        normals.push_back(normalVector);
    }
}

std::shared_ptr<Model> Cone::generate() {
    bool first;
    double slice_angle_increment=M_PI*2.0/nSlices;
    double height_increment=height/(1.0*nStacks);
    int index=2;
    Point3D top=Point3D(0.0f,height,0.0f,1);
    vertexes.push_back(Point3D());
    vertexes.push_back(top);
    normals.push_back(Point3D(0,-1,0));
    normals.push_back(Point3D(0,1,0));
    // Builds everything except base, from top to bottom
    for (int stack=nStacks-1;stack>=0;stack--) {
        float y=height_increment*stack;
        float stackRadius=((height-y)*radiusBase)/height;
        first=true;

        for (int slice=1;slice<=nSlices;slice++) {
            float x=cos(slice_angle_increment*slice)*stackRadius;
            float z=-sinf(slice_angle_increment*slice)*stackRadius;

            Point3D ponto =Point3D(x,y,z,index++);
            vertexes.push_back(ponto);

            std::pair<int,int> sliceAndStack(slice,stack);
            points[sliceAndStack]=ponto;

            if (first) {first=false;continue;}
            if (stack==nStacks-1) {
                addTopSlice(slice,stack,1);
                if (slice==nSlices) {
                    addTopSlice(slice,stack,0);
                }
            }
            else {
                addSquareSlice(slice,stack,1);
                if (slice==nSlices) {
                    addSquareSlice(slice,stack,0);
                }
            }
        }
        if(stack!=0)
            computeNormals(stack);
        else {
            computeNormals(stack);
            addBase(index);
        }
    }
    return std::make_shared<Model>(vertexes,faces,normals);
}