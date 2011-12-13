#ifndef DEF_PLANE
#define DEF_PLANE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"
#include "intersection.h"

class Plane : public Object {
 private :
  Vec4<float> normal;
  float originDistance;
 public :
  Plane(const Vec4<float> &normal, float originDistance, const Material &material);
  Intersection getIntersection(const Ray &ray);
  Vec4<float> getNormal();
  float getOriginDistance();
};

#endif
