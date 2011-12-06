#ifndef DEF_SPHERE
#define DEF_SPHERE

#define NO_INTERSECTION 3

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

using namespace std;

class Sphere : public Object {
 private :
  Vec4<float> center;
  float radius;
  Material material;
 public :
  Sphere(Vec4<float> center, float radius, Material material);
  Vec4<float> getCenter();
  float getRadius();
  Material getMaterial();
  Intersection getIntersection(Ray ray);
};

#endif

