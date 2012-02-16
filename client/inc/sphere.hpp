#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec3.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "object.hpp"

using namespace std;

class Sphere : public Object {
private :
    VEC3F center;
    float radius;
public :
    Sphere(const VEC3F& center,
           float radius,
           Material* material);
    void getIntersection(Ray& ray,
                         float* distance,
                         VEC3F* normal,
                         Material** material);
    VEC3F getCenter() const;
    float getRadius() const;
};

#endif

