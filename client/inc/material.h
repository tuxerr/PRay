#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "color.h"
#include "ray.h"
#include "vec4.h"
#include "scene.h"

class Material {
 public :
  virtual Color renderRay(const Ray &ray, const Vec4<float> &normal, const Scene &scene);
};

#endif
