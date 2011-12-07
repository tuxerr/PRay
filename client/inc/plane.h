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
  Plane(Vec4<float> normal, float originDistance, Material material);
  Intersection getIntersection(Ray ray);
  Vec4<float> getNormal();
  float getOriginDistance();
};

#endif
