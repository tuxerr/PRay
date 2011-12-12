#ifndef DEF_OBJECT
#define DEF_OBJECT

#define NO_INTERSECTION 3

#include "material.h"
#include "intersection.h"
#include "ray.h"

class Object {
 protected :
  Material material;
 public :
  Object(const Material &material);
  virtual Intersection getIntersection(const Ray &ray);
  Material getMaterial();
};

#endif
