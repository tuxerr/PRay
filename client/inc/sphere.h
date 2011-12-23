#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "vec3.h"
#include "material.h"
#include "ray.h"
#include "object.h"

using namespace std;

class Sphere : public Object {
private :
    Vec3<float> center;
    float radius;
public :
    Sphere(const Vec3<float>& center,
           float radius,
           Material* material);
    void getIntersection(Ray& ray,
                         float* distance,
                         Vec3<float>* normal,
                         Material** material);
    Vec3<float> getCenter() const;
    float getRadius() const;
};

#endif

