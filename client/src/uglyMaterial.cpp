#include "uglyMaterial.h"
#include <cmath>

UglyMaterial::UglyMaterial(const Color &color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::renderRay(const Ray & ray,
                              const Vec3<float> & normal,
                              Scene* /*nonUsedParameter*/) {

  float factor = std::abs( ray.getDirection().scalar(normal) / (ray.getDirection().norm() * normal.norm()) );

  return Color(factor * color.getR(),
               factor * color.getG(),
               factor * color.getB());
}

