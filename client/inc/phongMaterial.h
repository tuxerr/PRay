#ifndef DEF_PHONGMATERIAL
#define DEF_PHONGMATERIAL

#include "color.h"
#include "ray.h"
#include "material.h"
#include "vec4.h"

class PhongMaterial : public Material {
 private :
  
  Color color;

  /**
   * The ratio of reflection of the specular term of incoming light
   */
  float specularReflection;

  /**
   *  The ratio of reflection of the diffuse term of incoming light (Lambertian reflectance)
   */
  float diffuseReflection;

  /**
   *  The ratio of reflection of the ambient term present in all points in the scene rendered
   */
  float ambiantReflection;

  /**
   * Shininess constant for this material, which is larger for surfaces that are smoother and more mirror-like.
   * When this constant is large the specular highlight is small.
   */
  float shininess;

 public :
  PhongMaterial(const Color &color, float specularReflection, float diffuseReflection, float ambiantReflection, float shininess);
  Color getColor();
  float getSpecularReflection();
  float getDiffuseReflection();
  float getAmbiantReflection();
  float getShininess();
  Color renderRay(const Ray &ray, const Vec4<float> &normal, Scene *scene);  
};

#endif
