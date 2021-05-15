#include "../include/Group.h" 
#include "iostream"

Group::Group(const Group& g1) {
    transformations = g1.transformations;
    models=g1.models;
    nestedGroups=g1.nestedGroups;
}

void Group::addTransform(std::shared_ptr<Transform> t) {
    transformations.push_back(t);
}

void Group::addFile(std::string filename,Point3D * colors,float shininess) {
    models[filename]=Figure(colors[0],colors[1],shininess,colors[2],colors[3],filename);
}

void Group::addGroup(Group group) {
    nestedGroups.push_back(group);
}

std::unordered_set<std::string> Group::getModels() {
    std::unordered_set<std::string> ret;
    for (auto& m : models) {
            ret.insert(m.first);
        }
    for (auto& gg : nestedGroups) {
        std::unordered_set<std::string> models = gg.getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}