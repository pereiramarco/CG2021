#pragma once
#include <vector>
#include <map>
#include "Model.h"
#include "Triangulo.h"
#include "Ponto3D.h"

using namespace std;

class Sphere {
private:
    int radius,nStacks,nSlices;
    vector<Triangulo*> faces;
    map<pair<int,int>,Ponto3D*> points;
    void addTopOrBottom(bool top,int slice,int stack,int last);
    void addLastSlice(int last,int slice,int stack);
public:
    Sphere();
    Sphere(int radiusG,int slicesG,int stacksG);
    Model generate();
    void draw();
    void saveToFile(string filename);
};