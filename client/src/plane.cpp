#include "plane.h"

Plane::Plane(const Vec4<float> &normal, float originDistance, Material &material) :
  Object(&material), normal(normal), originDistance(originDistance)
{

}

Vec4<float> Plane::getNormal() {
  return normal;
}

float Plane::getOriginDistance() {
  return originDistance;
}

void Plane::getIntersection(Ray &ray, float *distance, Vec4<float> *normal, Material **material) {
  float PS = (this->normal).scalar(ray.getOrigin());
  float PD = (this->normal).scalar(ray.getDirection());
  if( PS <= originDistance || PD == 0 ) {
    *distance = -1;
  } else {
    float t = (originDistance - PS) / PD;
    *distance = t;
    *normal = this->normal;
    *material = &(*(this->material));
  }
}
