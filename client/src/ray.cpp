#include "ray.h"

Ray::Ray(const Vec3<float> &origin, const Vec3<float> &direction, Color &color) :
  origin(origin), direction(direction), color(color)
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
