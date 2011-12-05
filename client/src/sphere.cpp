/*#include "sphere.h"
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

Intersection* Sphere::getIntersection(Ray ray) {
  Vec4<float> SC= center - ray.getOrigin();
  Vec4<float> rayDirection = ray.getDirection();
  Intersection *result;
  if(SC.scalar(rayDirection) <= 0) {

    result = NULL;
  } else {
    Vec4<float> SA = SC.scalar(rayDirection)*rayDirection
    float nAC2 = SC.norm()^2 - SA.norm()^2;
    if(nAC2 >= radius^2) {
      result = NULL;
    } else {
      float nAB = sqrt(radius^2 - nAC2 );
      SB = SA - nAB*rayDirection;
      Vec4 intersection = ray.getCenter + SB;
      return = Intersection(intersection, (intersection - center).normalize(), material);
    }
  }
  return result;
}*/
