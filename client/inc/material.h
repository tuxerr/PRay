#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "vec4.h"
#include "ray.h"
#include "color.h"
//#include "scene.h"

class Scene;

class Material {
 public :
  virtual Color renderRay(const Ray &ray, const Vec4<float> &normal, Scene *scene) = 0;
};

#endif
