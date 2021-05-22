#pragma once
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Transformations/Transform.h"
#include "Transformations/Translation.h"
#include "Transformations/Rotation.h"
#include "Transformations/Scale.h"
#include "Figure.h"

class Group {
public:
    std::vector<std::shared_ptr<Transform>> transformations;
    std::unordered_map<std::string,Figure> models;
    std::vector<Group> nestedGroups;

    Group()=default;
    Group(const Group& g);

    void addTransform(std::shared_ptr<Transform> t);

    void addFile(std::string filename,Point3D * colors, float shininess, int texture);

    void addGroup(Group group);

    std::unordered_set<std::string> getModels();
};