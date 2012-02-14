#include "ray.hpp"

Ray::Ray(const Vec3<float> &origin, const Vec3<float> &direction, Color &color, int reflections) :
  origin(origin), direction(direction.normalize()), color(color), reflections(reflections)
{

}

Vec3<float> Ray::getOrigin() const {
  return origin;
}

Vec3<float> Ray::getDirection() const {
  return direction;
}

Color Ray::getColor() const {
  return color;
}
