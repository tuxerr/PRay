#ifndef DEF_UGLYMATERIAL
#define DEF_UGLYMATERIAL

#include "color.h"
#include "ray.h"
#include "material.h"
#include "vec4.h"

class UglyMaterial : public Material {
private:  
  Color color;
public :
  UglyMaterial(const Color &color);
  Color getColor();
  Color renderRay(const Ray &ray, const Vec4<float> &normal, Scene *scene);
};


#endif
