#include "ray.hpp"

Ray::Ray(const VEC3F &origin, const VEC3F &direction,
         Color &color, int reflections) :
    color(color),
    origin(origin),
    direction(direction.normalize()),
    reflections(reflections)
{

}

Color Ray::getColor() const {
    return color;
}
