#ifndef DEF_UGLYMATERIAL
#define DEF_UGLYMATERIAL

#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "vec3.hpp"

class UglyMaterial : public Material {
private:
  Color color;
public :
  UglyMaterial(const Color &color);
  ~UglyMaterial() {};
  Color getColor();
  Color renderRay(Ray &ray, float distance, const VEC3F &normal, Scene *scene);
};


#endif
