#include "sphere.h"
#include <math.h>

Sphere::Sphere(const Vec4<float> &center, 
               float radius, 
               const Material &material) :
    Object(material), 
    center(center), 
    radius(radius)
{

}

Vec4<float> Sphere::getCenter() {
    return center;
}

float Sphere::getRadius() {
    return radius;
}

int Sphere::getIntersection(const Ray &ray, 
                            float *distance, 
                            Vec4<float> *normal, 
                            Material *material) {
    Vec4<float> SC = center - ray.getOrigin();
    Vec4<float> rayDirection = ray.getDirection();
    if(SC.scalar(rayDirection) <= 0) {
        throw NO_INTERSECTION;
    } else {
        Vec4<float> SA = rayDirection*SC.scalar(rayDirection);
        float nAC2 = pow(SC.norm(), 2) - pow(SA.norm(), 2);
        if(nAC2 >= pow(radius, 2)) {
            throw NO_INTERSECTION;
        } else {
            float nAB = sqrt(pow(radius, 2) - nAC2 );
            Vec4<float> SB = SA - rayDirection*nAB;
            Vec4<float> intersection = ray.getOrigin() + SB;
            *distance = (intersection - center).norm();
            *normal = SB.normalize();
            *material = this->material;
            return 0;
        }
    }
    return 1;
}

