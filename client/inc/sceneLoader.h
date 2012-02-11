#ifndef DEF_SCENELOADER
#define DEF_SCENELOADER

#include <string>
#include <tinyxml.h>
#include "scene.h"

class SceneLoader {
public:
    int load(std::string nom, Scene** scene, int xRes, int yRes);

private:
    void readShape(TiXmlElement* node, list<Object*>* objects, Material* material);
    Material* readMaterial(TiXmlElement* node);
    Color readColor(TiXmlElement* node);
    Vec3<float> readVec3Float(TiXmlElement* node);
};

#endif
