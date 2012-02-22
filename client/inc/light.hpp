#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "color.hpp"
#include "vec3.hpp"

class Light {
private :
    Color color;
public :
    Light (const Color &color);
    Light (float grey =1);
    Light (float r, float g, float b);
    Color getColor();
    virtual VEC3F getDirection(VEC3F &point) = 0;
};

#endif
