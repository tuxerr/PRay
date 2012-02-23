#include "aabb.hpp"

AABB::AABB(float minX, float maxX,
           float minY, float maxY,
           float minZ, float maxZ) :
    minX(minX),
    maxX(maxX),
    minY(minY),
    maxY(maxY),
    minZ(minZ),
    maxZ(maxZ)
{
}

bool AABB::intersectRay(Ray &ray)
{
    // TODO
    return true;
}

/*
 * Ray-box intersection using IEEE numerical properties to ensure that the
 * test is both robust and efficient, as described in:
 *
 *      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
 *      "An Efficient and Robust Ray-Box Intersection Algorithm"
 *      Journal of graphics tools, 10(1):49-54, 2005
 *
 */
/*
bool AABB::intersectRay(Ray &ray, float t0, float t1)
{
    float rayPt[4];
    float rayDir[4];
    ray.getOrigin().getCoord(rayPt);
    ray.getDirection().getCoord(rayDir);

    float txmin, txmax, tymin, tymax, tzmin, tzmax;

    txmin = (parameters[r.sign[0]].x() - r.origin.x()) * r.inv_direction.x();
    txmax = (parameters[1-r.sign[0]].x() - r.origin.x()) * r.inv_direction.x();
    tymin = (parameters[r.sign[1]].y() - r.origin.y()) * r.inv_direction.y();
    tymax = (parameters[1-r.sign[1]].y() - r.origin.y()) * r.inv_direction.y();
    if ( (txmin > tymax) || (tymin > txmax) ) 
        return false;
    if (tymin > txmin)
        txmin = tymin;
    if (tymax < txmax)
        txmax = tymax;
    tzmin = (parameters[r.sign[2]].z() - r.origin.z()) * r.inv_direction.z();
    tzmax = (parameters[1-r.sign[2]].z() - r.origin.z()) * r.inv_direction.z();
    if ( (txmin > tzmax) || (tzmin > txmax) ) 
        return false;
    if (tzmin > txmin)
        txmin = tzmin;
    if (tzmax < txmax)
        txmax = tzmax;
    return ( (txmin < t1) && (txmax > t0) );
}
*/

/*
template<typename T> 
class Ray { 
public: 
    Ray(Vec3<T> orig, Vec3<T> dir) : 
        orig(orig), dir(dir), txmin(T(0)), txmax(std::numeric_limits<T>::max()) 
    { 
        invdir = T(1) / dir; 
        sign[0] = (invdir.x < 0); 
        sign[1] = (invdir.y < 0); 
        sign[2] = (invdir.z < 0); 
    } 
    Vec3<T> orig, dir;      /// ray orig and dir 
    mutable T txmin, txmax; /// ray min and max distances 
    Vec3<T> invdir; 
    int sign[3]; 
};

bool intersect(const Ray<T> &r) const { 
    T txmin, txmax, tymin, tymax, tzmin, tzmax; 
    txmin = (bounds[r.sign[0]].x - r.orig.x) * r.invdir.x; 
    txmax = (bounds[1-r.sign[0]].x - r.orig.x) * r.invdir.x; 
    tymin = (bounds[r.sign[1]].y - r.orig.y) * r.invdir.y; 
    tymax = (bounds[1-r.sign[1]].y - r.orig.y) * r.invdir.y; 
    if ((txmin > tymax) || (tymin > txmax)) 
        return false; 
    if (tymin > txmin) 
        txmin = tymin; 
    if (tymax < txmax) 
        txmax = tymax; 
    tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z; 
    tzmax = (bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z; 
    if ((txmin > tzmax) || (tzmin > txmax)) 
        return false; 
    if (tzmin > txmin) 
        txmin = tzmin; 
    if (tzmax < txmax) 
        txmax = tzmax; 
    if (txmin > r.txmin) 
        r.txmin = txmin; 
    if (txmax < r.txmax) 
        r.txmax = txmax; 
    return true; 
}
*/
