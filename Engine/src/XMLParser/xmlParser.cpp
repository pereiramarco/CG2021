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

Point3D readPoint(XMLElement* info) {
    const char * readX=info->Attribute("X");
    const char * readY=info->Attribute("Y");
    const char * readZ=info->Attribute("Z");
    float x=readX?atof(readX):0;
    float y=readY?atof(readY):0;
    float z=readZ?atof(readZ):0;
    return Point3D(x,y,z);
}

Group xmlContent::parseGroup(XMLElement * group) {
    Group g = Group();
    XMLElement * translation = group->FirstChildElement("translate");
    XMLElement * rotation = group->FirstChildElement("rotate");
    XMLElement * scale = group->FirstChildElement("scale");
    if (translation) {
        std::shared_ptr<Transform> t;
        if (const char * timeString = translation->Attribute("time")) {
            double time = atof(timeString);
            std::vector<Point3D> vector_points;
            for (XMLElement * point = translation->FirstChildElement("point");point;point = point->NextSiblingElement()) {
                vector_points.push_back(readPoint(point));
            }
            t = std::make_shared<Translation>(time,vector_points);
        }
        else {
            Point3D point = readPoint(translation);
            t = std::make_shared<Translation>(point.x,point.y,point.z);
        }
        g.addTransform(t);
    }
    if (rotation) {
        std::shared_ptr<Rotation> r;
        const char * readAngle;
        const char * readTime;

        const char * readX=rotation->Attribute("axisX");
        const char * readY=rotation->Attribute("axisY");
        const char * readZ=rotation->Attribute("axisZ");
        
        double axisx=readX?atof(readX):0;
        double axisy=readY?atof(readY):0;
        double axisz=readZ?atof(readZ):0;

        if (readTime=rotation->Attribute("time")) {
            const char * clockwise = rotation->Attribute("clockwise");
            r = std::make_shared<Rotation>(atof(readTime),std::string(clockwise).size(),axisx,axisy,axisz);
        }
        else {
            readAngle=rotation->Attribute("angle");
            r = std::make_shared<Rotation>(atof(readAngle),axisx,axisy,axisz);
        }
        g.addTransform(r);
    }
    if (scale) {
        const char * readX=scale->Attribute("scaleX");
        const char * readY=scale->Attribute("scaleY");
        const char * readZ=scale->Attribute("scaleZ");
        double scalex=readX?atof(readX):1;
        double scaley=readY?atof(readY):1;
        double scalez=readZ?atof(readZ):1;
        std::shared_ptr<Scale> s = std::make_shared<Scale>(scalex,scaley,scalez);
        g.addTransform(s);
    }
    XMLElement * models = group->FirstChildElement("models");
    if (models) {
        XMLElement * model;
        for (model=models->FirstChildElement();model;model=model->NextSiblingElement()) {
            const char * rr = model->Attribute("redColor");
            const char * gg = model->Attribute("greenColor");
            const char * bb = model->Attribute("blueColor");
            double red = rr?atof(rr):1;
            double green = gg?atof(gg):1;
            double blue = bb?atof(bb):1;
            g.addFile(std::string(model->Attribute("file")),red,green,blue);
        }
    }
    XMLElement *groupChild;
    for (groupChild = group->FirstChildElement("group");groupChild;groupChild=groupChild->NextSiblingElement()) {
        Group groupR = parseGroup(groupChild);
        g.addGroup(groupR); 
    }
    return g;
}

std::vector<Group> xmlContent::parse() {
    XMLDocument doc;
    int err = doc.LoadFile(filename.c_str());
    if(err == 0) {
        std:: cout << "Success" << std::endl;
        XMLElement * scene = doc.FirstChildElement("scene");
        XMLElement * group;
        for(group = scene->FirstChildElement();group != NULL;group = group->NextSiblingElement()) {
            Group g = parseGroup(group);
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
        std::unordered_set<std::string> models=g.getModels();
        for (auto& file : models) {
            ret.insert(file);
        }
    }
    return ret;
}
