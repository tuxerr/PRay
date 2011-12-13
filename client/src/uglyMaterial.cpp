#include "uglyMaterial.h"

UglyMaterial::UglyMaterial(const Color &color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::renderRay(const Ray &ray, const Vec4<float> &normal, const Scene &scene) {
  return color;
}

