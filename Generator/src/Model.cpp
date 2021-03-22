#include "../../Utils/Triangle.h"
#include "../include/Model.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

Model::Model(std::vector<Point3D*> vertixesG,std::vector<Triangle*> facesG) {
    nVertices=vertixesG.size();
    nTriangulos=facesG.size();
    vertixes=vertixesG;
    faces=facesG;
}

void Model::saveToFile(string filename) {
    ofstream fout(filename, ios::out); 
    fout<< to_string(nVertices) << " " << to_string(nTriangulos) << "\n";
    for (int i=0;i<nVertices;i++) {
        fout << to_string(vertixes[i]->x) << " " << to_string(vertixes[i]->y) << " " << to_string(vertixes[i]->z) << "\n"; 
    }
    for (int j=0;j<nTriangulos;j++) {
        fout << to_string(faces[j]->ponto1->index) << " " << to_string(faces[j]->ponto2->index) << " " << to_string(faces[j]->ponto3->index) << "\n"; 
    }
}