#include "../include/Torus.h"
#include <vector>
#include "../../Utils/Point3D.h"
#include "../include/Model.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>

Torus::Torus() {
    widenessRadius=1;
    thicknessRadius=1;
    nSides=10;
    nRings=10;
}

Torus::Torus(int widenessRadiusG,int thicknessRadiusG,int ringsG,int sidesG) {
    widenessRadius=widenessRadiusG;
    thicknessRadius=thicknessRadiusG;
    nSides=sidesG;
    nRings=ringsG;
}

void Torus::addSquare(int ring,int side,int not_last_ring,int not_last_side) {
    std::pair<int,int> topleft(ring-1,side-1),topright(ring,side-1);
    std::pair<int,int> bottomleft(ring-1,side),bottomright(ring,side);
    Point3D topRight=points[topright],topLeft=points[topleft];
    Point3D bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    Triangle t1=Triangle(topRight.index,topLeft.index,bottomLeft.index);
    Triangle t2=Triangle(topRight.index,bottomLeft.index,bottomRight.index);
    faces.push_back(t1);
    faces.push_back(t2);
}

void Torus::constructRing(int ring, float ring_angle) {
    Point3D nearCenterTop, farCenterTop, nearCenterBot, farCenterBot;
    float xNearCenter = (widenessRadius - thicknessRadius) * cosf(ring_angle), xFarCenter = (widenessRadius + thicknessRadius) * cosf(ring_angle);
    float zNearCenter = (widenessRadius - thicknessRadius) * sinf(ring_angle), zFarCenter = (widenessRadius + thicknessRadius) * sinf(ring_angle);
    nearCenterTop = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterTop = Point3D(xFarCenter,0,zFarCenter,index++);
    vertexes.push_back(nearCenterTop);
    vertexes.push_back(farCenterTop);
    nearCenterBot = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterBot = Point3D(xFarCenter,0,zFarCenter,index++);
    vertexes.push_back(nearCenterBot);
    vertexes.push_back(farCenterBot);
    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,-1,0));
    normals.push_back(Point3D(0,-1,0));
    texCoords.push_back(std::make_pair<float,float>(0,ring));
    texCoords.push_back(std::make_pair<float,float>(1,ring));
    texCoords.push_back(std::make_pair<float,float>(0,ring));
    texCoords.push_back(std::make_pair<float,float>(1,ring));
    if(ring == 0)
        return;
    Point3D beforeNearCenter, beforeFarCenter;
    beforeNearCenter = vertexes[vertexes.size()-8];
    beforeFarCenter = vertexes[vertexes.size()-7];
    Triangle t1=Triangle(farCenterTop.index,beforeNearCenter.index,nearCenterTop.index);
    Triangle t2=Triangle(farCenterTop.index,beforeFarCenter.index,beforeNearCenter.index);
    faces.push_back(t1);
    faces.push_back(t2);
    beforeNearCenter = vertexes[vertexes.size()-6];
    beforeFarCenter = vertexes[vertexes.size()-5];
    Triangle t3=Triangle(farCenterBot.index,nearCenterBot.index,beforeNearCenter.index);
    Triangle t4=Triangle(farCenterBot.index,beforeNearCenter.index,beforeFarCenter.index);
    faces.push_back(t3);
    faces.push_back(t4);
}

std::shared_ptr<Model> Torus::generate() {
    float ring_angle_increment=M_PI*2/nRings;
    float side_angle_increment=M_PI*2/nSides;
    index=0;
    for (int ring=0;ring<=nRings;ring++) {

        double ring_angle=ring*ring_angle_increment;
        bool first=true;
        float centerY = 0;
        float centerX = widenessRadius*cosf(ring_angle);
        float centerZ = widenessRadius*sin(ring_angle);

        if(nSides == 2) {
            constructRing(ring,ring_angle);
            continue;
        }

        for (int side=0;side<=nSides;side++) {

            double side_angle=side*side_angle_increment;
            float y=thicknessRadius*sinf(side_angle);
            float distHorizontal=thicknessRadius*cosf(side_angle);
            float z=(widenessRadius+distHorizontal)*sinf(ring_angle);
            float x=(widenessRadius+distHorizontal)*cosf(ring_angle);
            Point3D normal = Point3D(x-centerX,y,z-centerZ);
            normal.normalize();
            normals.push_back(normal);
            texCoords.push_back(std::make_pair<float,float>(side,ring));

            Point3D ponto=Point3D(x,y,z,index++);
            vertexes.push_back(ponto);

            //addPoint
            std::pair<int,int> ringAndSide(ring,side);
            points[ringAndSide]=ponto;
            if (first) {first=false;continue;} //primeira iteração de cada side deve apenas guardar o ponto
            if (ring==0) continue;//mete só os pontos e passa à frente
            else {//forma quadrados
                addSquare(ring,side,1,1);
                if (ring==nRings-1) //une quando está no último anel
                    addSquare(ring,side,0,1);
            }
            if (side==nSides-1) {  //une quando está no último side
                addSquare(ring,side,1,0);
                if (ring==nRings-1)  //une quando está no último anel do último side
                  addSquare(ring,side,0,0);  
            }
        }
    }
    return std::make_shared<Model>(vertexes,faces,normals,texCoords);
}