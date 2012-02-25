#ifndef DEF_RAY
#define DEF_RAY

#include "vec3.hpp"
#include "color.hpp"

class Ray {
private :
    VEC3F origin;
    VEC3F direction;
    Color color;
public :
    Ray(const VEC3F &origin, const VEC3F &direction, Color &color, int reflections = 0);
    VEC3F getOrigin() const;
    VEC3F getDirection() const;
    Color getColor() const;
    int reflections;
};

#endif
