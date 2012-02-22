#ifndef DEF_POINTLIGHT
#define DEF_POINTLIGHT

#include "vec3.hpp"
#include "color.hpp"
#include "light.hpp"

class PointLight : public Light {
private :
    VEC3F point;
public :
    PointLight(const Color &color,
	       const VEC3F &point);
    PointLight(float color,
	       const VEC3F &point);
    PointLight(float r,
	       float g,
	       float b,
	       const VEC3F &point);
    VEC3F getPoint();
    VEC3F getDirection();
    VEC3F getDirection(VEC3F &point);
};


#endif
