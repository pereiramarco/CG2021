#include "../include/Triangle.h"
#include "../include/Model.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

Model::Model(std::vector<Point3D> vertixesG,std::vector<Triangle> facesG,std::vector<Point3D> normals,std::vector<std::pair<float,float>> texCoords, float rad) {
    nVertices=vertixesG.size();
    nTriangulos=facesG.size();
    vertixesT=vertixesG;
    facesT=facesG;
    normalsT=normals;
    texCoordsT=texCoords;
    radius = rad;
}

void Model::saveToFile(std::string filename) {
    std::ofstream fout("../../Engine/models/" + filename, std::ios::out); 
    fout<< std::to_string(nVertices) << " " << std::to_string(nTriangulos) << " " << std::to_string(radius) << "\n";
    for (int i=0;i<nVertices;i++) {
        fout << std::to_string(vertixesT[i].x) << " " << std::to_string(vertixesT[i].y) << " " << std::to_string(vertixesT[i].z) << "\n"; 
    }
    for (int j=0;j<nTriangulos;j++) {
        fout << std::to_string(facesT[j].indexP1) << " " << std::to_string(facesT[j].indexP2) << " " << std::to_string(facesT[j].indexP3) << "\n"; 
    }
    for (int i=0;i<nVertices;i++) {
        fout << std::to_string(normalsT[i].x) << " " << std::to_string(normalsT[i].y) << " " << std::to_string(normalsT[i].z) << "\n"; 
    }
    for (int i=0;i<nVertices;i++) {
        fout << std::to_string(texCoordsT[i].first) << " " << std::to_string(texCoordsT[i].second) << "\n"; 
    }
}

