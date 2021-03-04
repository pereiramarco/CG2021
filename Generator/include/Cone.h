#pragma once
#include "Triangulo.h"
#include "Model.h"
#include <vector>
#include <map>

class Cone{
public:
    Cone();
    Cone(int radius,int heightG,int nSlicesG,int nStacksG);
    void generate();
    void draw();
    void saveToFile(string filename);
private:
    int radiusBase,height,nStacks,nSlices;
    vector<Triangulo*> faces;
    map<pair<int,int>,Ponto3D*> points;
    void addTop(int slice,int stack,int last);
    void addCircle(int last,int slice,int stack);
    void addSquare(int last,int slice,int stack);
};