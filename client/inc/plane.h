#ifndef DEF_PLANE
#define DEF_PLANE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

class Plane : public Object {
private :
    Vec4<float> normal;
    float originDistance;
public :
    Plane(const Vec4<float> &normal, float originDistance, Material &material);
    virtual int getIntersection(Ray &ray, float *distance, Vec4<float> *normal, 
                                Material *material);
    Vec4<float> getNormal();
    float getOriginDistance();
};

#endif
