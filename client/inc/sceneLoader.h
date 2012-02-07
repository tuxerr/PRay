#ifndef DEF_SCENELOADER
#define DEF_SCENELOADER

#include <string>
#include <tinyxml.h>
#include "scene.h"

class SceneLoader {
public:
  Scene load(std::string nom);
}

#endif
