#ifndef DEF_RENDERER
#define DEF_RENDERER

#include "logger.h"
#include "scene.h"

class Renderer {
public:
    Renderer(Scene *scene);
    
private:
    Scene *scene;
}

#endif
