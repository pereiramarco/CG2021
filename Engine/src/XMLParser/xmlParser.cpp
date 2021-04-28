#include "../../include/Group.h"
#include "../../include/Transformations/Transform.h"
#include "../../include/Transformations/Scale.h"
#include "../../include/Transformations/Translation.h"
#include "../../include/Transformations/Rotation.h"
#include "../../include/XMLParser/xmlParser.h"
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

std::shared_ptr<Point3D> readPoint(XMLElement* info) {
    const char * readX=info->Attribute("X");
    const char * readY=info->Attribute("Y");
    const char * readZ=info->Attribute("Z");
    float x=readX?atof(readX):0;
    float y=readY?atof(readY):0;
    float z=readZ?atof(readZ):0;
    return std::make_shared<Point3D>(x,y,z);
}

std::shared_ptr<Group> xmlContent::parseGroup(XMLElement * group) {
    std::shared_ptr<Group> g= std::make_shared<Group>();
    XMLElement * translation = group->FirstChildElement("translate");
    XMLElement * rotation = group->FirstChildElement("rotate");
    XMLElement * scale = group->FirstChildElement("scale");
    if (translation) {
        std::shared_ptr<Translation> t;
        if (const char * timeString = translation->Attribute("time")) {
            float time = atoi(timeString);
            std::vector<std::shared_ptr<Point3D>> vector_points;
            for (XMLElement * point = translation->FirstChildElement("point");point;point = point->NextSiblingElement()) {
                vector_points.push_back(readPoint(point));
            }
            t = std::make_shared<Translation>(time,vector_points);
        }
        else {
            std::shared_ptr<Point3D> point = readPoint(translation);
            t = std::make_shared<Translation>(point->x,point->y,point->z);
        }
        g->addTransform(t);
    }
    if (rotation) {
        int type=2;
        const char * readAngleOrTime;
        if (readAngleOrTime=rotation->Attribute("angle")) type=1;
        else 
            readAngleOrTime=rotation->Attribute("time");
        if (type==2) std::cout<<"I read time on rotate\n";
        float angleOrTime=atof(readAngleOrTime);
        const char * readX=rotation->Attribute("axisX");
        const char * readY=rotation->Attribute("axisY");
        const char * readZ=rotation->Attribute("axisZ");
        
        float axisx=readX?atof(readX):0;
        float axisy=readY?atof(readY):0;
        float axisz=readZ?atof(readZ):0;
        std::shared_ptr<Rotation> r = std::make_shared<Rotation>(type,angleOrTime,axisx,axisy,axisz);
        g->addTransform(r);
    }
    if (scale) {
        const char * readX=scale->Attribute("scaleX");
        const char * readY=scale->Attribute("scaleY");
        const char * readZ=scale->Attribute("scaleZ");
        float scalex=readX?atof(readX):1;
        float scaley=readY?atof(readY):1;
        float scalez=readZ?atof(readZ):1;
        std::shared_ptr<Scale> s = std::make_shared<Scale>(scalex,scaley,scalez);
        g->addTransform(s);
    }
    XMLElement * models = group->FirstChildElement("models");
    if (models) {
        XMLElement * model;
        for (model=models->FirstChildElement();model;model=model->NextSiblingElement()) {
            const char * rr = model->Attribute("redColor");
            const char * gg = model->Attribute("greenColor");
            const char * bb = model->Attribute("blueColor");
            float red = rr?atof(rr):1;
            float green = gg?atof(gg):1;
            float blue = bb?atof(bb):1;
            g->addFile(std::string(model->Attribute("file")),red,green,blue);
        }
    }
    XMLElement *groupChild;
    for (groupChild = group->FirstChildElement("group");groupChild;groupChild=groupChild->NextSiblingElement()) {
        std::shared_ptr<Group> groupR = parseGroup(groupChild);
        g->addGroup(groupR); 
    }
    return g;
}

std::vector<std::shared_ptr<Group> > xmlContent::parse() {
    XMLDocument doc;
    int err = doc.LoadFile(filename.c_str());
    if(err == 0) {
        std:: cout << "Success" << std::endl;
        XMLElement * scene = doc.FirstChildElement("scene");
        XMLElement * group;
        for(group = scene->FirstChildElement();group != NULL;group = group->NextSiblingElement()) {
            std::shared_ptr<Group> g = parseGroup(group);
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
