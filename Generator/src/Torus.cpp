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
    std::pair<int,int> topleft(ring-not_last_ring,side-not_last_side),topright(ring*not_last_ring,side-not_last_side);
    std::pair<int,int> bottomleft(ring-not_last_ring,side*not_last_side),bottomright(ring*not_last_ring,side*not_last_side);
    Point3D topRight=points[topright],topLeft=points[topleft];
    Point3D bottomLeft=points[bottomleft],bottomRight=points[bottomright];
    Triangle t1=Triangle(topRight.index,topLeft.index,bottomLeft.index);
    Triangle t2=Triangle(topRight.index,bottomLeft.index,bottomRight.index);
    faces.push_back(t1);
    faces.push_back(t2);
}

std::shared_ptr<Model> Torus::generate() {
    float ring_angle_increment=M_PI*2/nRings;
    float side_angle_increment=M_PI*2/nSides;
    int index=0;
    std::vector<Point3D> normals;

    std::vector<Point3D> vertixes;
    for (int ring=0;ring<nRings;ring++) {

        double ring_angle=ring*ring_angle_increment;
        bool first=true;
        float centerY = 0;
        float centerX = widenessRadius*cosf(ring_angle);
        float centerZ = widenessRadius*sin(ring_angle);

        for (int side=0;side<nSides;side++) {

            double side_angle=side*side_angle_increment;
            float y=thicknessRadius*sinf(side_angle);
            float distHorizontal=thicknessRadius*cosf(side_angle);
            float z=(widenessRadius+distHorizontal)*sinf(ring_angle);
            float x=(widenessRadius+distHorizontal)*cosf(ring_angle);

            Point3D normal = Point3D(x-centerX,y,z-centerZ);
            normal.normalize();
            normals.push_back(normal);

            Point3D ponto=Point3D(x,y,z,index++);
            vertixes.push_back(ponto);

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
    return std::make_shared<Model>(vertixes,faces,normals);
}