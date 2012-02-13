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
  Color getColor();
  Color renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene);
};


#endif
