#include "../include/Triangle.h"
#include "../include/Model.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

Model::Model(std::vector<std::shared_ptr<Point3D>> vertixesG,std::vector<std::shared_ptr<Triangle>> facesG) {
    nVertices=vertixesG.size();
    nTriangulos=facesG.size();
    vertixes=vertixesG;
    faces=facesG;
}

void Model::saveToFile(std::string filename) {
    std::ofstream fout("../../Engine/models/"+filename, std::ios::out); 
    fout<< std::to_string(nVertices) << " " << std::to_string(nTriangulos) << "\n";
    for (int i=0;i<nVertices;i++) {
        fout << std::to_string(vertixes[i]->x) << " " << std::to_string(vertixes[i]->y) << " " << std::to_string(vertixes[i]->z) << "\n"; 
    }
    for (int j=0;j<nTriangulos;j++) {
        fout << std::to_string(faces[j]->ponto1->index) << " " << std::to_string(faces[j]->ponto2->index) << " " << std::to_string(faces[j]->ponto3->index) << "\n"; 
    }
}