#include "intersection.h"

Intersection::Intersection(Vec4<float> point, Vec4<float> normal, float distance, Material material) :
  point(point), normal(normal), distance(distance), material(material)
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

Material Intersection::getMaterial() {
  return material;
}
