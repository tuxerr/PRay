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

  float r = factor * color.getR();
  float g = factor * color.getG();
  float b = factor * color.getB();

  if(r>1) {
    r=1;
  }
  if(g>1) {
    g=1;
  }
  if(b>1) {
    b=1;
  }  

  return Color(r, g, b);
               
}

