#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include <algorithm>
#include "object.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "logger.hpp"

class Triangle : public Object {
private :
    VEC3F a;
    VEC3F b;
    VEC3F c;
    VEC3F normal;
    VEC3F na;
    VEC3F nb;
    VEC3F nc;
public :
    Triangle(VEC3F &a, VEC3F &b, VEC3F &c,
             VEC3F &na, VEC3F &nb, VEC3F &nc, 
             VEC3F &normal, Material *material);
    VEC3F getA() ;
    VEC3F getB() ;
    VEC3F getC() ;
    VEC3F getNA() ;
    VEC3F getNB() ;
    VEC3F getNC() ;
    VEC3F getNormal() ;
    VEC3F getNormal(VEC3F &point);
    void getIntersection(Ray &ray, float *distance, VEC3F *normal,
                         Material **material);
};

#endif
