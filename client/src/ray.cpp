#include "ray.hpp"

Ray::Ray(const VEC3F &origin, const VEC3F &direction, Color &color, int reflections) :
  origin(origin), 
  direction(direction.normalize()), 
  color(color), 
  reflections(reflections)
{

}

VEC3F Ray::getOrigin() const {
  return origin;
}

VEC3F Ray::getDirection() const {
  return direction;
}

Color Ray::getColor() const {
  return color;
}
