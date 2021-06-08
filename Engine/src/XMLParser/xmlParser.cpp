#ifndef __APPLE__
#endif
#ifdef __APPLE__
#include <il.h>
#else
#include <GL/glew.h>
#include <IL/il.h>
#endif
#include "../../include/Group.h"
#include "../../include/Transformations/Transform.h"
#include "../../include/Transformations/Scale.h"
#include "../../include/Transformations/Translation.h"
#include "../../include/Transformations/Rotation.h"
#include "../../include/XMLParser/xmlParser.h"
#include "../../include/Lights/Light.h"
#include "../../include/Lights/DirectionalLight.h"
#include "../../include/Lights/PointLight.h"
#include "../../include/Lights/SpotLight.h"
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

void xmlContent::parseLight(XMLElement * light) {
    XMLElement * lightEl = light->FirstChildElement();
    std::string type(lightEl->Attribute("type"));
    if(type=="POINT") {
        float x = atof(lightEl->Attribute("posX"));
        float y = atof(lightEl->Attribute("posY"));
        float z = atof(lightEl->Attribute("posZ"));
        std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(x,y,z);
        lights.push_back(pl);
    }
    else if(type=="DIRECTIONAL") {
        float x = atof(lightEl->Attribute("dirX"));
        float y = atof(lightEl->Attribute("dirY"));
        float z = atof(lightEl->Attribute("dirZ"));
        std::shared_ptr<DirectionalLight> dl = std::make_shared<DirectionalLight>(x,y,z);
        lights.push_back(dl);
    }
    else if(type=="SPOT") {
        float x = atof(lightEl->Attribute("posX"));
        float y = atof(lightEl->Attribute("posY"));
        float z = atof(lightEl->Attribute("posZ"));
        float dx = atof(lightEl->Attribute("dirX"));
        float dy = atof(lightEl->Attribute("dirY"));
        float dz = atof(lightEl->Attribute("dirZ"));
        float angle = atof(lightEl->Attribute("angle"));
        std::shared_ptr<SpotLight> sl = std::make_shared<SpotLight>(x,y,z,dx,dy,dz,angle);
        lights.push_back(sl);
    }
    else {
        std::cout << "Error parsing lights\n";
        exit(1);
    }
}

void xmlContent::parseColor(Point3D colors[],float& shininess, XMLElement * model) {
    const char * dr = model->Attribute("diffR");
    const char * dg = model->Attribute("diffG");
    const char * db = model->Attribute("diffB");
    const char * sr = model->Attribute("specR");
    const char * sg = model->Attribute("specG");
    const char * sb = model->Attribute("specB");
    const char * er = model->Attribute("emissR");
    const char * eg = model->Attribute("emissG");
    const char * eb = model->Attribute("emissB");
    const char * ar = model->Attribute("ambR");
    const char * ag = model->Attribute("ambG");
    const char * ab = model->Attribute("ambB");
    const char * shin = model->Attribute("shin");
    double dred = dr?atof(dr):-1;
    double dgreen = dg?atof(dg):-1;
    double dblue = db?atof(db):-1;
    double sred = sr?atof(sr):-1;
    double sgreen = sg?atof(sg):-1;
    double sblue = sb?atof(sb):-1;
    double ered = er?atof(er):-1;
    double egreen = eg?atof(eg):-1;
    double eblue = eb?atof(eb):-1;
    double ared = ar?atof(ar):-1;
    double agreen = ag?atof(ag):-1;
    double ablue = ab?atof(ab):-1;
    shininess = shin?atof(shin):-1;
    colors[0] = Point3D(dred,dgreen,dblue);
    colors[1] = Point3D(sred,sgreen,sblue);
    colors[2] = Point3D(ared,agreen,ablue);
    colors[3] = Point3D(ered,egreen,eblue);
}

void xmlContent::loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

    ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)("../textures/" + s).c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	//std::cout << "Image Width: " << tw << std::endl;
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	textures[s] = texID;

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
            Point3D colors[4]; // 1. Diffuse   2. Specular   3. Ambient   4. Emissive
            float shininess;
            parseColor(colors,shininess,model);
            int texID = 0;
            const char * texture = model->Attribute("texture");
            if(texture) {
                std::string stringTexture(texture);
                if(textures.find(stringTexture) == textures.end())
                    loadTexture(stringTexture);
                texID = textures[stringTexture];
            }
            g.addFile(std::string(model->Attribute("file")),colors,shininess,texID);
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
        XMLElement * node;

        for(node = scene->FirstChildElement();node != NULL;node = node->NextSiblingElement()) {
            std::string name(node->Name());
            if(name=="group") {
                Group g = parseGroup(node);
                groups.push_back(g);
            }
            else if(name=="lights") {
                parseLight(node);
            }
            else {
                std::cout << "Error parsing xml!" << "\n";
                exit(2);
            }
        }
    }
    else {
        doc.PrintError();
    }
    return groups;
}

std::vector<std::shared_ptr<Light>> xmlContent::getLights() {
    return lights;
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
