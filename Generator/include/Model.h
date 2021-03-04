#pragma once
#include <vector>
#include "Ponto3D.h"
#include <string>

using namespace std;

class Model{
private:
    int numOfTriangles;
    vector<Ponto3D> points;

public:
    Model();
    void saveToFile(string filename);
};