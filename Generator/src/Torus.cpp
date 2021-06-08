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

// Pega em 4 pontos (os 2 em questão e outros dois, sendo esses o do ring anterior e o do side anterior) e forma um quadrado com eles
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

// Caso especial quand o torus se trata de um plano, ou seja, apenas tem 2 lados e não tem volume
void Torus::constructRing(int ring, float ring_angle) {
    Point3D nearCenterTop, farCenterTop, nearCenterBot, farCenterBot;
    // Pega no x e z mais próximos do centro e x e z mais longe do centro de cada ring e guarda-os na estrutura dos vértices
    float xNearCenter = (widenessRadius - thicknessRadius) * cosf(ring_angle), xFarCenter = (widenessRadius + thicknessRadius) * cosf(ring_angle);
    float zNearCenter = (widenessRadius - thicknessRadius) * sinf(ring_angle), zFarCenter = (widenessRadius + thicknessRadius) * sinf(ring_angle);
    nearCenterTop = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterTop = Point3D(xFarCenter,0,zFarCenter,index++);
    vertexes.push_back(nearCenterTop);
    vertexes.push_back(farCenterTop);
    // Os pontos são repetidos para se gerar dois quadrados, um que aponta para cima, e outro que aponta para baixo
    // De forma a se conseguir ver ambos os lados do torus
    nearCenterBot = Point3D(xNearCenter,0,zNearCenter,index++);
    farCenterBot = Point3D(xFarCenter,0,zFarCenter,index++);
    vertexes.push_back(nearCenterBot);
    vertexes.push_back(farCenterBot);
    // Normais dos dois quadrados
    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,1,0));
    normals.push_back(Point3D(0,-1,0));
    normals.push_back(Point3D(0,-1,0));
    // TexCoords de cada quadrado
    texCoords.push_back(std::make_pair<float,float>(0.0f,float(ring)));
    texCoords.push_back(std::make_pair<float,float>(1.0f,float(ring)));
    texCoords.push_back(std::make_pair<float,float>(0.0f,float(ring)));
    texCoords.push_back(std::make_pair<float,float>(1.0f,float(ring)));
    if(ring == 0)
        return;
    Point3D beforeNearCenter, beforeFarCenter;
    // Vai buscar os dois pontos do ring anterior e forma dois quadrados
    // Não é possível usar os mesmos pontos pois têm normais associadas diferentes!
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

// Geração de um torus deitado
std::shared_ptr<Model> Torus::generate() {
    // Incrementos de ângulos para cada iteração
    float ring_angle_increment=M_PI*2/nRings;
    float side_angle_increment=M_PI*2/nSides;
    // Indice a dar a cada ponto para depois ser identificado na geração de triângulos a partir de indexação
    index=0;
    for (int ring=0;ring<=nRings;ring++) {

        double ring_angle=ring*ring_angle_increment;
        bool first=true;
        // Determinação das coordenadas do ponto central de cada ring do torus
        float centerY = 0;
        float centerX = widenessRadius*cosf(ring_angle);
        float centerZ = widenessRadius*sin(ring_angle);

        // Caso especial quando o o torus não tem volume, logo é tratado como um plano (tendo as normais em conta)
        if(nSides == 2) {
            constructRing(ring,ring_angle);
            continue;
        }

        for (int side=0;side<=nSides;side++) {
        
            double side_angle=side*side_angle_increment;
            // Determinação dos pontos referentes a cada side do ring
            float y=thicknessRadius*sinf(side_angle);
            float distHorizontal=thicknessRadius*cosf(side_angle);
            float z=(widenessRadius+distHorizontal)*sinf(ring_angle);
            float x=(widenessRadius+distHorizontal)*cosf(ring_angle);
            // Normal consiste na direção do centro do ring até ao ponto a definir desse ring, normalizada
            Point3D normal = Point3D(x-centerX,y,z-centerZ);
            normal.normalize();
            normals.push_back(normal);
            // Como as coordenadas de textura se repetem a cada unidade cartesiana, a instrução abaixo
            // faz com que a textura se repita em cada side de cada ring
            texCoords.push_back(std::make_pair<float,float>(float(side),float(ring)));

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