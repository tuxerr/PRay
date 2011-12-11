#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "color.h"
#include "ray.h"
#include "intersection.h"
#include "vec4.h"

class Material {
 public :
  virtual Color getViewedColor(Ray ray, Vec4<float> normal);
};

#endif
