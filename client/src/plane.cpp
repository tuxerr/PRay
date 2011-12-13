#include "plane.h"

Plane::Plane(const Vec4<float> &normal, float originDistance, const Material &material) :
  Object(materia), normal(normal), originDistance(originDistance)
{

}

Vec4<float> Plane::getNormal() {
  return normal;
}

float Plane::getOriginDistance() {
  return originDistance;
}

/*We are considering plane as a half space*/
Intersection Plane::getIntersection(const Ray &ray) {
  float PS = normal.scalar(ray.getOrigin());
  float PD = normal.scalar(ray.getDirection());
  if( PS <= originDistance || PD == 0 ) {
    throw NO_INTERSECTION;
  } else {
    float t = (originDistance - PS) / PD;
    return Intersection(normal, t, material);
  }
}
