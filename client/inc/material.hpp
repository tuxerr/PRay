#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
//#include "scene.h"

class Scene;

class Material {
 public :
  virtual Color renderRay(Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) = 0;
};

#endif
