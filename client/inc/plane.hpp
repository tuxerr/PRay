#ifndef DEF_PLANE
#define DEF_PLANE

#include "vec3.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "object.hpp"

class Plane : public Object {
private :
    VEC3F normal;
    VEC3F point;
public :
    Plane(const VEC3F &normal, const VEC3F &point, Material *material);
    void getIntersection(Ray &ray, float *distance, VEC3F *normal,
                         Material **materialIntersection);
    VEC3F getNormal();
    VEC3F getPoint();
};

#endif
