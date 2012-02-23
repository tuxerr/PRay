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
    aabb = new AABB(0, 1, 0, 1, 0, 1); // TODO
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

    VEC3F L = center - ray.getOrigin();
    VEC3F V = ray.getDirection().normalize();
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
            VEC3F OP = ray.getOrigin() + V*(*distance) - center;
            *normal = OP.normalize();
            *materialIntersection = material;
        }
    }
}

