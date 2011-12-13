#include "ray.h"

Ray::Ray(const Vec4<float> &origin, const Vec4<float> &direction) :
  origin(origin), direction(direction)
{

}

Vec4<float> Ray::getOrigin() {
  return origin;
}

Vec4<float> Ray::getDirection() {
  return direction;
}

Color Ray::getColor() {
  return color;
}
