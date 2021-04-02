#pragma once

#include <iostream>
#include "tinyxml2.h"
#include "../Group.h"
#include "../Figure.h"
#include <string>
#include <vector>

using namespace tinyxml2;

class xmlContent {
    public:
        xmlContent();
        xmlContent(char* st);
        xmlContent(std::string st);
        std::shared_ptr<Group> parseGroup(XMLElement * group);
        std::vector<std::shared_ptr<Group>> parse();
        std::unordered_set<std::string> getModels();
    private:
        std::string filename;
        std::vector<std::shared_ptr<Group>> groups;

};