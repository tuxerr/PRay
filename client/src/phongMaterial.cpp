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
  shininess(shininess)
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

Color PhongMaterial::renderRay(const Ray &ray, const Vec3<float> &normal, Scene *scene) {

  float r = 0;
  float g = 0;
  float b = 0;

  r += color.getR()*ambiantReflection;
  
  for(DirectionalLight l : scene->getDirectionalLights()) {
    r += color.getR()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    r += color.getR()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
	   shininess));
  }
  
  r<255 ? r=r : r=255;


  g += color.getG()*ambiantReflection;
  
  for(DirectionalLight l : scene->getDirectionalLights()) {
    g += color.getG()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    g += color.getG()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
		shininess));
  }
  
  g<255 ? g=g : g=255;


  b += color.getB()*ambiantReflection;
  
  for(DirectionalLight l : scene->getDirectionalLights()) {
    b += color.getB()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    b += color.getB()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
		shininess));
  }
  
  b<255 ? b=b : b=255;

    return Color(r, g, b);

}
