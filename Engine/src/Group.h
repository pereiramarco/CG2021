#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <unordered_set>
#include "Transformations/Transform.h"
#include "Transformations/Translation.h"
#include "Transformations/Rotation.h"
#include "Transformations/Scale.h"

class Group {
public:
    std::vector<Transform*> transformations;
    std::vector<std::string> files;
    std::vector<Group*> nestedGroups;

    Group()=default;

    void addTransform(Transform * t);

    void addFile(std::string filename);

    void addGroup(Group * group);

    std::unordered_set<std::string> getModels();
};