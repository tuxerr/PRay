#include "ray.h"

Ray::Ray(const Vec4<float> &origin, const Vec4<float> &direction, Color &color) :
  origin(origin), direction(direction), color(color)
{

}

Vec4<float> Ray::getOrigin() const {
  return origin;
}

Vec4<float> Ray::getDirection() const {
  return direction;
}

Color Ray::getColor() const {
  return color;
}
