#include "uglyMaterial.h"
#include "logger.h"
#include <cmath>

UglyMaterial::UglyMaterial(const Color &color) :
  color(color)
{

}

Color UglyMaterial::getColor() {
  return color;
}

Color UglyMaterial::renderRay(const Ray & ray,
			      float distance,
                              const Vec3<float> & normal,
                              Scene* /*nonUsedParameter*/) {

  //  Logger::log(LOG_DEBUG)<< "UGLYMATERIAL" <<endl;  
  //  Logger::log(LOG_DEBUG)<< distance <<endl;  

  float factor = std::abs( ray.getDirection().scalar(normal) / (ray.getDirection().norm() * normal.norm()) );

  return Color(factor * color.getR(),
               factor * color.getG(),
               factor * color.getB());
}

