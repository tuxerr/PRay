#include "uglyMaterial.h"

UglyMaterial::UglyMaterial(Color color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::getViewedColor(Ray ray, Intersection intersection) {
  return color;
}

