#ifndef DEF_SCENELOADER
#define DEF_SCENELOADER

#include <list>
#include <set>
#include <string>
#include <tinyxml.h>
#include <SDL/SDL.h>
#include "scene.hpp"
#include "logger.hpp"
#include "settings.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "light.hpp"
#include "directionalLight.hpp"
#include "pointLight.hpp"
#include "ambientLight.hpp"
#include "vec3.hpp"
#include "material.hpp"
#include "phongMaterial.hpp"
#include "uglyMaterial.hpp"


class SceneLoader {
public:
    int load(std::string nom, Scene** scene, int xRes, int yRes);

private:
    void readShape(TiXmlElement* node, list<Object*>* objects, Material* material);
    Material* readMaterial(TiXmlElement* node);
    Color readColor(TiXmlElement* node);
    VEC3F readVec3Float(TiXmlElement* node);
};

#endif
