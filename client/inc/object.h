#ifndef DEF_OBJECT
#define DEF_OBJECT

#define NO_INTERSECTION 3

#include "material.h"
#include "intersection.h"
#include "object.h"
#include "ray.h"

class Object {
 protected :
  Material material;
 public :
  Object(Material material);
  virtual Intersection getIntersection(Ray ray);
  Material getMaterial();
};

#endif
