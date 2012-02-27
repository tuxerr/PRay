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
    float surfaceArea;
    AABB(float minX, float maxX,
         float minY, float maxY,
         float minZ, float maxZ);
    bool intersectRay(Ray &ray, float distanceMax = FLT_MAX);
    float getVolume();
};

#endif
