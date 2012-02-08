#include "phongMaterial.h"
#include "logger.h"
#include "directionalLight.h"
#include "math.h"
#include "scene.h"


PhongMaterial::PhongMaterial(const Color &color, 
			     float specularReflection, 
			     float diffuseReflection, 
			     float ambiantReflection, 
			     float shininess) :
  color(color), 
  specularReflection(specularReflection), 
  diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), 
  shininess(shininess),
  reflectivity(1)
{

}

PhongMaterial::PhongMaterial(const Color &color, 
			     float specularReflection, 
			     float diffuseReflection, 
			     float ambiantReflection, 
			     float shininess,
			     float reflectivity) :
  color(color), 
  specularReflection(specularReflection), 
  diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), 
  shininess(shininess),
  reflectivity(reflectivity)
{

}

Color PhongMaterial::getColor() {
  return color;
}

float PhongMaterial::getSpecularReflection() {
  return specularReflection;
}

float PhongMaterial::getDiffuseReflection() {
  return diffuseReflection;
}

float PhongMaterial::getAmbiantReflection() {
  return ambiantReflection;
}

float PhongMaterial::getShininess() {
  return shininess;
}

float PhongMaterial::getReflectivity() {
  return reflectivity;
}

Color PhongMaterial::renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) {

  float r = 0;
  float g = 0;
  float b = 0;

  Vec3<float> point = ray.getOrigin() + ray.getDirection()*distance;
  list<DirectionalLight> lights = scene->visibleLights(point);

  float diffuse;
  float specular;

  r += color.getR()*ambiantReflection;
  g += color.getG()*ambiantReflection;
  b += color.getB()*ambiantReflection;  

  for(DirectionalLight l : lights) {
    diffuse = diffuseReflection*fabs(l.getDirection().scalar(normal));
    specular = specularReflection*fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), shininess));

    r += color.getR()*diffuse;
    g += color.getG()*diffuse;
    b += color.getB()*diffuse;

    r += color.getR()*specular;
    g += color.getG()*specular;
    b += color.getB()*specular;
    
  }
  
  if(r>255) {
    r=255;
  }
  if(g>255) {
    g=255;
  }
  if(b>255) {
    b=255;
  }  

  return Color(r, g, b);

}
