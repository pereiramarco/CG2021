#pragma once
#include "Triangulo.h"
#include <vector>
#include "Ponto3D.h"
#include <string>
#include <map>

class Model{
public:
    Model(int nVertices,int nTriangulosG,std::vector<Ponto3D*> vertixesG,std::vector<Triangulo*> faces);
    void saveToFile(std::string filename);
private:
    int nVertices,nTriangulos;
    std::vector<Triangulo*> faces;
    std::vector<Ponto3D*> vertixes;
};