#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "object.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Triangle : public Object {
private :
  VEC3F a;
  VEC3F b;
  VEC3F c;
  VEC3F normal;
public :
  Triangle(VEC3F &a, VEC3F &b, VEC3F &c, Material *material);
  VEC3F getA() ;
  VEC3F getB() ;
  VEC3F getC() ;
  VEC3F getNormal() ;
  void getIntersection(Ray &ray, float *distance, VEC3F *normal,
		       Material **material);
};

#endif
