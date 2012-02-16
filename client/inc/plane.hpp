#ifndef DEF_PLANE
#define DEF_PLANE

#include "vec3.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "object.hpp"

class Plane : public Object {
private :
    VEC3F normal;
    float originDistance;
public :
    Plane(const VEC3F &normal, float originDistance, Material &material);
    void getIntersection(Ray &ray, float *distance, VEC3F *normal,
                         Material **material);
    VEC3F getNormal();
    float getOriginDistance();
};

#endif
