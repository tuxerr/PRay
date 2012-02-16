#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "object.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Triangle : public Object {
private :
  Vec3<float> a;
  Vec3<float> b;
  Vec3<float> c;
  Vec3<float> normal;
  Vec3<float> na;
  Vec3<float> nb;
  Vec3<float> nc;
public :
  Triangle(Vec3<float> &a, Vec3<float> &b, Vec3<float> &c, Material *material);
  Triangle(Vec3<float> &a, Vec3<float> &b, Vec3<float> &c,
	   Vec3<float> &na, Vec3<float> &nb, Vec3<float> &nc, Material *material);
  Vec3<float> getA() ;
  Vec3<float> getB() ;
  Vec3<float> getC() ;
  Vec3<float> getNA() ;
  Vec3<float> getNB() ;
  Vec3<float> getNC() ;
  Vec3<float> getNormal() ;
  Vec3<float> getNormal(float u, float v);
  void getIntersection(Ray &ray, float *distance, Vec3<float> *normal,
		       Material **material);
};

#endif
