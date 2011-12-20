#include "logger.h"
#include "sphere.h"
#include <math.h>

Sphere::Sphere(const Vec4<float> &center,
               float radius,
               Material* material) :
    Object(material),
    center(center),
    radius(radius)
{

}

Vec4<float> Sphere::getCenter() const {
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
                             Vec4<float>* normal,
                             Material** materialIntersection) {

    // http://www.cs.princeton.edu/courses/archive/fall00/
    //                                 cs426/lectures/raycast/sld013.htm

    Vec4<float> L = center - ray.getOrigin();
    Vec4<float> V = ray.getDirection().normalize();
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
            Vec4<float> OP = ray.getOrigin() + V*(*distance) - center;
            *normal = OP.normalize();
            *materialIntersection = material;
        }
    }
}

