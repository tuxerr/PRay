#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "vec3.h"
#include "ray.h"
#include "color.h"
//#include "scene.h"

class Scene;

class Material {
 public :
  virtual Color renderRay(const Ray &ray, const Vec3<float> &normal, Scene *scene) = 0;
};

#endif
