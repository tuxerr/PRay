#include "logger.hpp"
#include "sphere.hpp"
#include <math.h>

Sphere::Sphere(const VEC3F &center,
               float radius,
               Material* material) :
    Object(material, NULL),
    center(center),
    radius(radius)
{
    float centerCoord[4];
    center.getCoord(centerCoord);
    aabb = new AABB(centerCoord[0] - radius, centerCoord[0] + radius,
                    centerCoord[1] - radius, centerCoord[1] + radius,
                    centerCoord[2] - radius, centerCoord[2] + radius);
}

VEC3F Sphere::getCenter() const {
    return center;
}

float Sphere::getRadius() const {
    return radius;
}

/**
 * *distance < 0 if no intersection was found
 */
void Sphere::getIntersection(Ray& ray,
                             float* distance,
                             VEC3F* normal,
                             Material** materialIntersection) {

    // http://www.cs.princeton.edu/courses/archive/fall00/
    //                                 cs426/lectures/raycast/sld013.htm

    VEC3F L = center - ray.origin;
    VEC3F V = ray.direction.normalize();
    float t_ca = L.scalar(V);
    if (t_ca < 0) {
        *distance = -1;
    } else {
        float d2 = L.scalar(L) - t_ca * t_ca;
        float r2 = radius * radius;
        if (d2 > r2) {
            *distance = -1;
        } else {
            float t_hc = sqrt(r2 - d2);
            float t1 = t_ca - t_hc;
            float t2 = t_ca + t_hc;
            *distance = (t1<t2) ? t1 : t2;
            VEC3F OP = ray.origin + V*(*distance) - center;
            *normal = OP.normalize();
            *materialIntersection = material;
        }
    }
}

