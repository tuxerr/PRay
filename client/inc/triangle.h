#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "object.h"
#include "vec3.h"
#include "ray.h"

class Triangle : public Object {
private :
  Vec3<float> a;
  Vec3<float> b;
  Vec3<float> c;
  Vec3<float> normal;
public :
  Triangle(Vec3<float> &a, Vec3<float> &b, Vec3<float> &c, Material *material);
  Vec3<float> getA() ;
  Vec3<float> getB() ;
  Vec3<float> getC() ;
  Vec3<float> getNormal() ;
  void getIntersection(Ray &ray, float *distance, Vec3<float> *normal,
		       Material **material);
};

#endif
