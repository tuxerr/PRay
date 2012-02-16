#ifndef DEF_PLANE
#define DEF_PLANE

#include "vec3.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "object.hpp"

class Plane : public Object {
private :
    Vec3<float> normal;
    float originDistance;
public :
    Plane(const Vec3<float> &normal, float originDistance, Material &material);
    void getIntersection(Ray &ray, float *distance, Vec3<float> *normal,
                         Material **material);
    Vec3<float> getNormal();
    float getOriginDistance();
};

#endif