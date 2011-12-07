#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

using namespace std;

class Sphere : public Object {
 private :
  Vec4<float> center;
  float radius;
 public :
  Sphere(Vec4<float> center, float radius, Material material);
  Intersection getIntersection(Ray ray);
  Vec4<float> getCenter();
  float getRadius();
};

#endif

