#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"
#include "intersection.h"

using namespace std;

class Sphere : public Object {
 private :
  Vec4<float> center;
  float radius;
 public :
  Sphere(const Vec4<float> &center, float radius, const Material &material);
  Intersection getIntersection(Ray ray);
  Vec4<float> getCenter();
  float getRadius();
};

#endif

