#include "xmlParser.h"

xmlContent::xmlContent() {
    filename = "../config.xml";
}

xmlContent::xmlContent(char* st) {
    filename = std::string(st);
}

xmlContent::xmlContent(std::string st) {
    filename = st;
}

void xmlContent::parse() {
    XMLDocument doc;
    int err = doc.LoadFile(filename.c_str());
    if(err == 0) {
        std:: cout << "Success" << std::endl;
    }
    else {
        doc.PrintError();
    }
    XMLElement * scene = doc.FirstChildElement("scene");
    XMLElement * model;
    for(model = scene->FirstChildElement();model != NULL;model = model->NextSiblingElement()) {
        files.push_back(model->Attribute("file"));
    }

}

std::vector<const char*> xmlContent::getModels() {
    return files;
}