#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "ray.h"
#include "material.h"
#include "vec3.h"

class Object {
protected :
    Material *material;
public :
    Object(Material* material);
    virtual ~Object();
    virtual void getIntersection(Ray& ray,
                                 float* distance,
                                 Vec3<float>* normal,
                                 Material** material) = 0;
    Material* getMaterial();
};

#endif
