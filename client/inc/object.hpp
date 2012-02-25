#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "ray.hpp"
#include "material.hpp"
#include "vec3.hpp"
#include "aabb.hpp"
#include "logger.hpp"
#include "material.hpp"

class Object {
protected :
    Material* material;
    AABB* aabb;
public :
    Object(Material* material, AABB* aabb);
    virtual ~Object();
    virtual void getIntersection(Ray& ray,
                                 float* distance,
                                 VEC3F* normal,
                                 Material** material) = 0;
    Material* getMaterial();
    AABB* getAABB();
};

#endif
