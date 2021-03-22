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

void Group::ident(int identNumber) {
    for (int i=0;i<identNumber;i++) std::cout<< "\t";
}

void Group::print(int identNumber) {
    ident(identNumber);
    std::cout<< "Transformations:" <<std::endl;
    for (auto& t : transformations) {
        ident(identNumber);
        std::cout<<"\t" << t->toString()<<std::endl;
    }
    ident(identNumber);
    std::cout<< "Files:" <<std::endl;
    for (auto& f : files) {
        ident(identNumber);
        std::cout<<"\t" << f <<std::endl; 
    }
    ident(identNumber);
    std::cout<< "NESTEDGROUPS:" <<std::endl;
    for (auto& g : nestedGroups) {
        ident(identNumber);
        g->print(identNumber+1);
    }
    ident(identNumber);
    std::cout<< "ENDNESTEDGROUPS:" <<std::endl;
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