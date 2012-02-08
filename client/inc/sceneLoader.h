#ifndef DEF_SCENELOADER
#define DEF_SCENELOADER

#include <string>
#include <tinyxml.h>
#include "scene.h"

#define TIXML_USE_STL

class SceneLoader {
public:
    int load(std::string nom, Scene** scene, int xRes, int yRes);

private:
    Object* readShape(TiXmlElement* node, Material* material);
    Material* readMaterial(TiXmlElement* node);
    Color readColor(TiXmlElement* node);
    Vec3<float> readVec3Float(TiXmlElement* node);

};

#endif
