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
    Triangle t;
    std::pair<int,int> point_before(slice-1,stack);
    std::pair<int,int> point_after(slice,stack);
    Point3D top = vertexes[slice];
    Point3D before=points[point_before];
    Point3D after=points[point_after]; 
    t = Triangle(top.index,before.index,after.index);
    this->faces.push_back(t);
}

void Cone::addCircleSlice(int slice,int stack,int not_last) {
    Point3D middle=Point3D();
    std::pair<int,int> before(slice-not_last,stack),after(slice*not_last+(1-not_last),stack);
    Point3D afterPoint=points[after],beforePoint=points[before];
    Triangle t=Triangle(middle.index,afterPoint.index,beforePoint.index); //é visto debaixo logo está mudada a ordem
    faces.push_back(t);
}

void Cone::addSquareSlice(int slice,int stack) {
    std::pair<int,int> bottomleft(slice-1,stack),bottomright(slice,stack),topleft(slice-1,stack+1),topright(slice,stack+1);
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
        texCoords.push_back(std::make_pair<float,float>(cos(slice_angle_increment*slice) * 0.1875 + 0.8125,sin(slice_angle_increment*slice) * 0.1875 + 0.1875));
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
    for(int i = 0; i <= nSlices; i++) {
        std::pair<int,int> beforepoint((i-1==-1?nSlices:i-1),stack);
        std::pair<int,int> afterpoint((i==nSlices?0:i+1),stack);
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
    int index=1;
    float tex_x_increment = 1.0/(1.0*nSlices);
    float tex_y_increment = 0.625/(1.0*nStacks);
    vertexes.push_back(Point3D());
    normals.push_back(Point3D(0,-1,0));
    texCoords.push_back(std::make_pair<float,float>(0.8125,0.1875));
    for(int i = 0; i < nSlices; i++) {
        Point3D top=Point3D(0.0f,height,0.0f,index++);
        vertexes.push_back(top);
        normals.push_back(Point3D(0,1,0));
        double x_tex_coord = i * tex_x_increment * 1.0 + (tex_x_increment / 2.0);
        texCoords.push_back(std::make_pair<float,float>(float(x_tex_coord),1.0f));
    }
    // Builds everything except base, from top to bottom
    for (int stack=nStacks-1;stack>=0;stack--) {
        float y=height_increment*stack;
        float stackRadius=((height-y)*radiusBase)/height;
        first=true;

        for (int slice=0;slice<=nSlices;slice++) {
            float x=cos(slice_angle_increment*slice)*stackRadius;
            float z=-sinf(slice_angle_increment*slice)*stackRadius;

            Point3D ponto =Point3D(x,y,z,index++);
            vertexes.push_back(ponto);
            texCoords.push_back(std::make_pair<float,float>(slice*tex_x_increment,stack*tex_y_increment + 0.375));

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
                addSquareSlice(slice,stack);
            }
        }
        if(stack!=0)
            computeNormals(stack);
        else {
            computeNormals(stack);
            addBase(index);
        }
    }
    return std::make_shared<Model>(vertexes,faces,normals,texCoords);
}