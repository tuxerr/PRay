#include "aabb.hpp"

AABB::AABB(float minX, float maxX,
           float minY, float maxY,
           float minZ, float maxZ) :
    minX(minX),
    maxX(maxX),
    minY(minY),
    maxY(maxY),
    minZ(minZ),
    maxZ(maxZ),
    surfaceArea(2.0 * ((maxX - minX) * ((maxY - minY) + (maxZ - minZ))
                       + (maxY - minY) * (maxZ - minZ)))
{
}

// http://www.ics.uci.edu/~arvo/EECS204/code/latest/aabb.cpp
bool AABB::intersectRay(Ray &ray, float distanceMax)
{
    float dir[4];
    ray.getDirection().getCoord(dir);
    float orig[4];
    ray.getOrigin().getCoord(orig);
    float r, s, t;
    float min( 0.0 );
    float max( distanceMax );

    if( dir[0] > 0 ) // Looking in positive X direction.
    {
        if( orig[0] > maxX ) return false;
        r = 1.0 / dir[0];
        s = ( minX - orig[0] ) * r; if( s > min ) min = s;
        t = ( maxX - orig[0] ) * r; if( t < max ) max = t;
    }
    else if( dir[0] < 0.0 ) // Looking in negative X direction.
    {
        if( orig[0] < minX ) return false;
        r = 1.0 / dir[0];
        s = ( maxX - orig[0] ) * r; if( s > min ) min = s;
        t = ( minX - orig[0] ) * r; if( t < max ) max = t;
    }
    else if( orig[0] < minX || orig[0] > maxX ) return false;

    if( min > max ) return false; // Degenerate interval.

    if( dir[1] > 0 ) // Looking in positive Y direction.
    {
        if( orig[1] > maxY ) return false;
        r = 1.0 / dir[1];
        s = ( minY - orig[1] ) * r; if( s > min ) min = s;
        t = ( maxY - orig[1] ) * r; if( t < max ) max = t;
    }
    else if( dir[1] < 0 ) // Looking in negative Y direction.
    {
        if( orig[1] < minY ) return false;
        r = 1.0 / dir[1];
        s = ( maxY - orig[1] ) * r; if( s > min ) min = s;
        t = ( minY - orig[1] ) * r; if( t < max ) max = t;
    }
    else if( orig[1] < minY || orig[1] > maxY ) return false;

    if( min > max ) return false; // Degenerate interval.

    if( dir[2] > 0 ) // Looking in positive Z direction.
    {
        if( orig[2] > maxZ ) return false;
        r = 1.0 / dir[2];
        s = ( minZ - orig[2] ) * r; if( s > min ) min = s;
        t = ( maxZ - orig[2] ) * r; if( t < max ) max = t;
    }
    else if( dir[2] < 0 ) // Looking in negative Z direction.
    {
        if( orig[2] < minZ ) return false;
        r = 1.0 / dir[2];
        s = ( maxZ - orig[2] ) * r; if( s > min ) min = s;
        t = ( minZ - orig[2] ) * r; if( t < max ) max = t;
    }
    else if( orig[2] < minZ || orig[2] > maxZ ) return false;

    // There is a hit if and only if the intersection interval [min,max]
    // is not degenerate.
    return min <= max;
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
