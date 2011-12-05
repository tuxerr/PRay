#include "sphere.h"
#include <math.h>

Sphere::Sphere(Vec4<float> center, float radius, Material material) :
  center(center), radius(radius), Object(material)
{

}

Vec4<float> Sphere::getCenter() {
  return center;
}

float Sphere::getRadius() {
  return radius;
}

/*Dirty function, cleaning compulsory*/
Intersection Sphere::getIntersection(Ray ray) {
  Vec4<float> SC = center - ray.getOrigin();
  Vec4<float> rayDirection = ray.getDirection();
  if(SC.scalar(rayDirection) <= 0) {
    throw NO_INTERSECTION;
  } else {
    Vec4<float> SA = SC.scalar(rayDirection)*rayDirection;
    float nAC2 = pow(SC.norm(), 2) - pow(SA.norm(), 2);
    if(nAC2 >= pow(radius, 2)) {
      throw NO_INTERSECTION;
    } else {
      float nAB = sqrt(pow(radius, 2) - nAC2 );
      SB = SA - rayDirection*nAB;
      Vec4<float> intersection = ray.getOrigin + SB;
      return Intersection(intersection, (intersection - center).normalize(), material);
    }
  }
}
