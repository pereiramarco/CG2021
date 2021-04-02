#pragma once
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <memory>
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
    std::unordered_map<std::string,std::shared_ptr<Figure>> models;
    std::vector<std::shared_ptr<Group>> nestedGroups;

    Group()=default;

    void addTransform(std::shared_ptr<Transform> t);

    void addFile(std::string filename,float red,float green,float blue);

    void addGroup(std::shared_ptr<Group> group);

    std::unordered_set<std::string> getModels();
};