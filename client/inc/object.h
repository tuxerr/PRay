#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "material.h"
#include "intersection.h"

class Object {
 protected :
  Material material;
 public :
  Object(Material material);
  virtual Intersection getIntersection();
  Material getMaterial();
};

#endif
