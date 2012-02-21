#ifndef DEF_AABB
#define DEF_AABB

#include <cfloat>
#include "ray.hpp"

class AABB {
public :
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
    AABB(float minX, float maxX,
         float minY, float maxY,
         float minZ, float maxZ);
    bool intersectRay(Ray &ray, float t0 = FLT_MIN, float t1 = FLT_MAX);
}

#endif
