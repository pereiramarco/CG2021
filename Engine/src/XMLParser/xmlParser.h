#pragma once

#include <iostream>
#include "tinyxml2.h"
#include <string>
#include <vector>

using namespace tinyxml2;

class xmlContent {
    public:
        xmlContent();
        xmlContent(char* st);
        xmlContent(std::string st);
        void parse();
        std::vector<std::string> getModels();
    private:
        std::string filename;
        std::vector<const char*> files;

};