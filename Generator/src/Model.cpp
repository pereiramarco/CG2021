#include "../include/Triangle.h"
#include "../include/Model.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

Model::Model(std::vector<Point3D> vertixesG,std::vector<Triangle> facesG) {
    nVertices=vertixesG.size();
    nTriangulos=facesG.size();
    vertixesT=vertixesG;
    facesT=facesG;
}

void Model::saveToFile(std::string filename) {
    std::ofstream fout("../../Engine/models/" + filename, std::ios::out); 
    fout<< std::to_string(nVertices) << " " << std::to_string(nTriangulos) << "\n";
    for (int i=0;i<nVertices;i++) {
        fout << std::to_string(vertixesT[i].x) << " " << std::to_string(vertixesT[i].y) << " " << std::to_string(vertixesT[i].z) << "\n"; 
    }
    for (int j=0;j<nTriangulos;j++) {
        fout << std::to_string(facesT[j].indexP1) << " " << std::to_string(facesT[j].indexP2) << " " << std::to_string(facesT[j].indexP3) << "\n"; 
    }
}

