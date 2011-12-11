#include "uglyMaterial.h"

UglyMaterial::UglyMaterial(Color color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::getViewedColor(Ray ray, Vec4<float> normal) {
  return color;
}

