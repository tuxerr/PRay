#ifndef DEF_DIRECTIONALLIGHT
#define DEF_DIRECTIONALLIGHT


#include "vec3.hpp"
#include "color.hpp"
#include "light.hpp"

class DirectionalLight : public Light {
private :
    VEC3F direction;
public :
    DirectionalLight(const Color &color,
                     const VEC3F &direction);
    DirectionalLight(float color,
                     const VEC3F &direction);
    DirectionalLight(float r,
                     float g,
                     float b,
                     const VEC3F &direction);
    VEC3F getDirection();
};

#endif
