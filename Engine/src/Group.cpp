#include "Group.h" 
#include "iostream"

void Group::addTransform(Transform * t) {
    transformations.push_back(t);
}

void Group::addFile(std::string filename) {
    files.push_back(filename);
}

void Group::addGroup(Group * group) {
    nestedGroups.push_back(group);
}

std::unordered_set<std::string> Group::getModels() {
    std::unordered_set<std::string> ret;
    for (auto& f : files) {
            ret.insert(f);
        }
    for (auto& gg : nestedGroups) {
        std::unordered_set<std::string> models = gg->getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}