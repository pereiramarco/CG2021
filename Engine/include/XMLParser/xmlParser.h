#pragma once

#include <iostream>
#include "tinyxml2.h"
#include "../Group.h"
#include "../Figure.h"
#include "../Lights/Light.h"
#include <string>
#include <vector>
#include <memory>

using namespace tinyxml2;

class xmlContent {
    public:
        xmlContent();
        xmlContent(char* st);
        xmlContent(std::string st);
        Group parseGroup(XMLElement * group);
        std::vector<Group> parse();
        std::unordered_set<std::string> getModels();
        void parseLight(XMLElement * light);
        std::vector<std::shared_ptr<Light>> getLights();
        void parseColor(Point3D colors[],float& shininess,XMLElement * model);
    private:
        std::string filename;
        std::vector<Group> groups;
        std::vector<std::shared_ptr<Light>> lights;

};