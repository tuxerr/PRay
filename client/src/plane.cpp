#include "plane.h"


Plane::Plane(Vec4<float> normal, float originDistance, Material material) :
  normal(normal), originDistance(originDistance), Object(material)
{

}

Vec4<float> Plane::getNormal() {
  return normal;
}

float Plane::getOriginDistance() {
  return originDistance;
}

/*We are considering plane as a half space*/
Intersection Plane::getIntersection(Ray ray) {
  float PS = normal.scalar(ray.getOrigin());
  float PD = normal.scalar(ray.getDirection());
  if( PS <= originDistance || PD == 0 ) {
    throw NO_INTERSECTION;
  } else {
    float t = (originDistance - PS) / PD;
    return Intersection(ray.getOrigin() + ray.getDirection()*t, normal, material);
  }
}
