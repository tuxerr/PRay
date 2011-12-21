#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "object.h"
#include "vec4.h"
#include "ray.h"

class Triangle : public Object {
private :
  Vec4<float> a;
  Vec4<float> b;
  Vec4<float> c;
  Vec4<float> normal;
public :
  Triangle(Vec4<float> &a, Vec4<float> &b, Vec4<float> &c, Material *material);
  Vec4<float> getA() ;
  Vec4<float> getB() ;
  Vec4<float> getC() ;
  Vec4<float> getNormal() ;
  void getIntersection(Ray &ray, float *distance, Vec4<float> *normal, 
		       Material **material);
};

#endif
