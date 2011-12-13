#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

using namespace std;

class Sphere : public Object {
 private :
  Vec4<float> center;
  float radius;
 public :
  Sphere(const Vec4<float> &center, float radius, const Material &material);
  int getIntersection(const Ray &ray, float *distance, Vec4<float> *normal, Material *material);
  Vec4<float> getCenter();
  float getRadius();
};

#endif

