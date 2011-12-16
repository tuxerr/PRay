#ifndef DEF_OBJECT
#define DEF_OBJECT

#define NO_INTERSECTION 3

#include "ray.h"
#include "material.h"
#include "vec4.h"

class Object {
protected :
    Material *material;
public :
    Object(Material* material);
    virtual void getIntersection(Ray& ray, 
                                 float* distance, 
                                 Vec4<float>* normal, 
                                 Material* material);
    Material getMaterial();
};

#endif
