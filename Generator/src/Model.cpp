#include "../../Utils/Triangulo.h"
#include "../include/Model.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

Model::Model(int nVerticesG,int nTriangulosG,std::vector<Ponto3D*> vertixesG,std::vector<Triangulo*> facesG) {
    nVertices=nVerticesG;
    nTriangulos=nTriangulosG;
    vertixes=vertixesG;
    faces=facesG;
}

void Model::saveToFile(string filename) {
    ofstream fout("../../Engine/"+filename, ios::out) ; 
    fout<< to_string(nVertices) << " " << to_string(nTriangulos) << "\n";
    for (int i=0;i<nVertices;i++) {
        fout << to_string(vertixes[i]->x) << " " << to_string(vertixes[i]->y) << " " << to_string(vertixes[i]->z) << "\n"; 
    }
    for (int j=0;j<nTriangulos;j++) {
        fout << to_string(faces[j]->ponto1->index) << " " << to_string(faces[j]->ponto2->index) << " " << to_string(faces[j]->ponto3->index) << "\n"; 
    }
}