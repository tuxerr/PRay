#include "intersection.h"

Intersection::Intersection(Vec4<float> point, Vec4<float> normal, Material material) :
  point(point), normal(normal), material(material)
{

}

Vec4<float> Intersection::getPoint() {
  return point;
}

Vec4<float> Intersection::getNormal() {
  return normal;
}

Material Intersection::getMaterial() {
  return material;
}
