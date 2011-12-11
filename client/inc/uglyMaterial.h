#ifndef DEF_UGLYMATERIAL
#define DEF_UGLYMATERIAL

#include "color.h"
#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "vec4.h"

class UglyMaterial : public Material {
private:  
  Color color;
public :
  UglyMaterial(Color color);
  Color getColor();
  Color getViewedColor(Ray ray, Vec4<float> normal);
};


#endif
