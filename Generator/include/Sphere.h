#pragma once
#include <vector>
#include <map>
#include "../../Utils/Ponto3D.h"
#include <string>
#include "../../Utils/Triangulo.h"
#include "Model.h"

class Sphere {
private:
    int radius,nStacks,nSlices;
    std::vector<Triangulo*> faces;
    std::map<std::pair<int,int>,Ponto3D*> points;
    void addTopOrBottom(bool top,int slice,int stack,int last);
    void addSlice(int last,int slice,int stack);
public:
    Sphere();
    Sphere(int radiusG,int slicesG,int stacksG);
    Model* generate();
};