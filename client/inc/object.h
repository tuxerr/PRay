#ifndef DEF_OBJECT
#define DEF_OBJECT

#define NO_INTERSECTION 3

#include "ray.h"
//#include "material.h"

class Material;

class Object {
protected :
    Material *material;
public :
    Object(Material* material);
    virtual int getIntersection(Ray& ray, 
                                float* distance, 
                                Vec4<float>* normal, 
                                Material* material);
    Material getMaterial();
};

#endif
