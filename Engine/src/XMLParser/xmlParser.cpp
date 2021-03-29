#include "../Group.h"
#include "../Transformations/Transform.h"
#include "../Transformations/Scale.h"
#include "../Transformations/Translation.h"
#include "../Transformations/Rotation.h"
#include "xmlParser.h"
#include "unordered_set"

xmlContent::xmlContent() {
    filename = "../configs/config.xml";
}

xmlContent::xmlContent(char* st) {
    filename = std::string(st);
}

xmlContent::xmlContent(std::string st) {
    filename = st;
}

Group * xmlContent::parseGroup(XMLElement * group) {
    Group * g= new Group();
    XMLElement * translation = group->FirstChildElement("translate");
    XMLElement * rotation = group->FirstChildElement("rotate");
    XMLElement * scale = group->FirstChildElement("scale");
    if (translation) {
        const char * readX=translation->Attribute("X");
        const char * readY=translation->Attribute("Y");
        const char * readZ=translation->Attribute("Z");
        float x=readX?atof(readX):0;
        float y=readY?atof(readY):0;
        float z=readZ?atof(readZ):0;
        Translation* t = new Translation(x,y,z);
        g->addTransform(t);
    }
    if (rotation) {
        const char * readDegrees=rotation->Attribute("angle");
        const char * readX=rotation->Attribute("axisX");
        const char * readY=rotation->Attribute("axisY");
        const char * readZ=rotation->Attribute("axisZ");
        float angle=readDegrees?atof(readDegrees):0;
        float axisx=readX?atof(readX):0;
        float axisy=readY?atof(readY):0;
        float axisz=readZ?atof(readZ):0;
        Rotation* r = new Rotation(angle,axisx,axisy,axisz);
        g->addTransform(r);
    }
    if (scale) {
        const char * readX=scale->Attribute("scaleX");
        const char * readY=scale->Attribute("scaleY");
        const char * readZ=scale->Attribute("scaleZ");
        float scalex=readX?atof(readX):1;
        float scaley=readY?atof(readY):1;
        float scalez=readZ?atof(readZ):1;
        Scale* s = new Scale(scalex,scaley,scalez);
        g->addTransform(s);
    }
    XMLElement * models = group->FirstChildElement("models");
    if (models) {
        XMLElement * model;
        for (model=models->FirstChildElement();model;model=model->NextSiblingElement()) {
            g->addFile(std::string(model->Attribute("file")));
        }
    }
    XMLElement *groupChild;
    for (groupChild = group->FirstChildElement("group");groupChild;groupChild=groupChild->NextSiblingElement()) {
        Group * groupR = parseGroup(groupChild);
        g->addGroup(groupR); 
    }
    return g;
}

std::vector<Group*> xmlContent::parse() {
    XMLDocument doc;
    int err = doc.LoadFile(filename.c_str());
    if(err == 0) {
        std:: cout << "Success" << std::endl;
        XMLElement * scene = doc.FirstChildElement("scene");
        XMLElement * group;
        for(group = scene->FirstChildElement();group != NULL;group = group->NextSiblingElement()) {
            Group *g = parseGroup(group);
            groups.push_back(g);
        }
    }
    else {
        doc.PrintError();
    }
    return groups;
}

std::unordered_set<std::string> xmlContent::getModels() {
    std::unordered_set<std::string> ret;
    for (auto& g : groups) {
        std::unordered_set<std::string> models=g->getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}
