#ifndef DEF_PHONGMATERIAL
#define DEF_PHONGMATERIAL

#include "color.h"
#include "ray.h"
#include "material.h"
#include "vec3.h"

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

  float transparency;

  float refractiveIn;

  float refractiveOut;

 public :
  PhongMaterial(const Color &color, 
		float specularReflection, 
		float diffuseReflection, 
		float ambiantReflection, 
		float shininess,
		float reflectivity,
		float transparency,
		float refractiveIn,
		float refractiveOut);

  PhongMaterial(const Color &color, 
		float specularReflection, 
		float diffuseReflection, 
		float ambiantReflection, 
		float shininess,
		float reflectivity);


  /*  Color getColor();
  float getSpecularReflection();
  float getDiffuseReflection();
  float getAmbiantReflection();
  float getShininess();
  float getReflectivity();*/
  Color renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene);
};

#endif
