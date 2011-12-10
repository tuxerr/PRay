#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "color.h"
#include "ray.h"
#include "intersection.h"

class Material {
 public :
  Material();
  virtual Color getViewedColor(Ray ray, Intersection intersection);
};

#endif
