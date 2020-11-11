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

    float transparency;

    float refractiveIn;

    float refractiveOut;

    void addReflection(float &r, float &g, float &b,
		       Ray &ray, VEC3F &point,
		       const VEC3F &normal, Scene *scene);

    void addRefraction(float &r, float &g, float &b,
		       Ray &ray, VEC3F &point,
		       const VEC3F &normal, Scene *scene);

public :
    PhongMaterial(const Color &color, 
		  float specularReflection, 
		  float diffuseReflection, 
		  float ambiantReflection, 
		  float shininess,
		  float reflectivity,
		  float transparency,
		  float refractiveIn = 1,
		  float refractiveOut = 1);

    ~PhongMaterial() {};

    Color renderRay(Ray &ray, float distance, const VEC3F &normal, Scene *scene);
};

#endif
