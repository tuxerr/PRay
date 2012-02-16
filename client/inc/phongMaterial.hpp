#ifndef DEF_PHONGMATERIAL
#define DEF_PHONGMATERIAL

#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "vec3.hpp"

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

  /**
   * 1 for a perfect mirror, 0 for no reflectivity
   */
  float reflectivity;

  int maxReflections;

  float transparency;

  float refractiveIn;

  float refractiveOut;

  VEC3F reflect(VEC3F normal, VEC3F incident);

  VEC3F refract(VEC3F normal, VEC3F incident, float n1, float n2);

  float reflectance(VEC3F normal, VEC3F incident, float n1, float n2);

  float rSchlick2(VEC3F normal, VEC3F incident, float n1, float n2);


 public :
  PhongMaterial(const Color &color, 
		float specularReflection, 
		float diffuseReflection, 
		float ambiantReflection, 
		float shininess,
		float reflectivity = 0.9,
		int maxReflections = 9,
		float transparency = 0.7,
		float refractiveIn = 1.1,
		float refractiveOut = 1);

  Color renderRay(Ray &ray, float distance, const VEC3F &normal, Scene *scene);
};

#endif
