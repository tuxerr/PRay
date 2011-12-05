/*#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

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
  Intersection* getIntersection(Ray ray);
};

#endif*/
