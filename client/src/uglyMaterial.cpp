#include "uglyMaterial.h"

UglyMaterial::UglyMaterial(const Color &color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::renderRay(const Ray & /*nonUsedParameter*/, 
                              const Vec4<float> & /*nonUsedParameter*/, 
                              Scene* /*nonUsedParameter*/) {
  return color;
}

