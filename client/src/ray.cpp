#include "ray.h"

Ray::Ray(Vec4<float> origin, Vec4<float> direction) :
  origin(origin), direction(direction)
{

}

Vec4<float> Ray::getOrigin() {
  return origin;
}

Vec4<float> Ray::getDirection() {
  return direction;
}
