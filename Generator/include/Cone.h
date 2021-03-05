#pragma once
#include "Triangulo.h"
#include <vector>
#include "Ponto3D.h"
#include <string>
#include <map>

class Cone{
public:
    Cone();
    Cone(int radius,int heightG,int nSlicesG,int nStacksG);
    void generate();
    void draw();
    void saveToFile(std::string filename);
private:
    int radiusBase,height,nStacks,nSlices;
    std::vector<Triangulo*> faces;
    std::map<std::pair<int,int>,Ponto3D*> points;
    void addTop(int slice,int stack,int last);
    void addCircle(int last,int slice,int stack);
    void addSquare(int last,int slice,int stack);
};