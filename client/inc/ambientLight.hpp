#ifndef DEF_AMBIENTLIGHT
#define DEF_AMBIENTLIGHT

#include "light.hpp"

class AmbientLight : public Light {
public :
    AmbientLight (const Color &color);
    AmbientLight (float grey =1);
    AmbientLight (float r, float g, float b);
};

#endif
