#include "../include/Group.h" 
#include "iostream"

void Group::addTransform(std::shared_ptr<Transform> t) {
    transformations.push_back(t);
}

void Group::addFile(std::string filename,float red,float green,float blue) {
    models[filename]=std::make_shared<Figure>(red,green,blue,filename);
}

void Group::addGroup(std::shared_ptr<Group> group) {
    nestedGroups.push_back(group);
}

std::unordered_set<std::string> Group::getModels() {
    std::unordered_set<std::string> ret;
    for (auto& m : models) {
            ret.insert(m.first);
        }
    for (auto& gg : nestedGroups) {
        std::unordered_set<std::string> models = gg->getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}