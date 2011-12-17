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

    Vec4<float> SC = center - ray.getOrigin();
    Vec4<float> rayDirection = ray.getDirection().normalize();
    if(SC.scalar(rayDirection) <= 0) {
        *distance = -1;
    } else {
        Vec4<float> SA = rayDirection*SC.scalar(rayDirection);
        float nAC2 = pow(SC.norm(), 2) - pow(SA.norm(), 2); // AC² = SC² - SA²
        if(nAC2 >= pow(radius, 2)) {
            *distance = -1;
        } else {
	    float nAB = sqrt(pow(radius, 2) - nAC2 ); // AB = sqrt( r² - AC² ) 
            Vec4<float> SB = SA - rayDirection*nAB;
            Vec4<float> intersection = ray.getOrigin() + SB;
            *distance = (intersection - center).norm();
            *normal = SB.normalize();
            *materialIntersection = material;
        }
    }
}

