#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec4.h"
#include "material.h"
#include "ray.h"
#include "object.h"

using namespace std;

class Sphere : public Object {
private :
    Vec4<float> center;
    float radius;
public :
    Sphere(const Vec4<float>& center, 
           float radius, 
           Material& material);
    int getIntersection(Ray& ray, 
                        float* distance,
                        Vec4<float>* normal,
                        Material* material);
    Vec4<float> getCenter() const;
    float getRadius() const;
};

#endif

