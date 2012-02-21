#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "ray.hpp"
#include "material.hpp"
#include "vec3.hpp"

class Object {
protected :
    Material *material;
public :
    Object(Material* material);
    virtual ~Object();
    virtual void getIntersection(Ray& ray,
                                 float* distance,
                                 VEC3F* normal,
                                 Material** material) = 0;
    Material* getMaterial();
};

#endif
