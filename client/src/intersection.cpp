#include "intersection.h"

Intersection::Intersection(Vec4<float> point, Vec4<float> normal, float distance, Object* object, Ray ray) :
  point(point), normal(normal), distance(distance), object(object), ray(ray)
{

}

Vec4<float> Intersection::getPoint() {
  return point;
}

Vec4<float> Intersection::getNormal() {
  return normal;
}

float Intersection::getDistance() {
  return distance;
}

Object Intersection::getObject() {
  return *object;
}

Ray Intersection::getRay() {
  return ray;
}

Color Intersection::getViewedColor() {
  return object->getMaterial().getViewedColor(ray, normal);
}

