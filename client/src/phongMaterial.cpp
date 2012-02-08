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

Color PhongMaterial::renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) {

  //  Logger::log(LOG_DEBUG)<< "PHONGMATERIAL" <<endl;  

  float r = 0;
  float g = 0;
  float b = 0;

  Vec3<float> point = ray.getOrigin() + ray.getDirection()*distance;
  list<DirectionalLight> lights = scene->visibleLights(point);
  //list<DirectionalLight> lights = scene->getDirectionalLights();

  r += color.getR()*ambiantReflection;
  
  //  Logger::log(LOG_DEBUG)<< lights <<endl;  

  for(DirectionalLight l : lights) {
    r += color.getR()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    r += color.getR()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
	   shininess));
  }
  
  r<255 ? r=r : r=255;


  g += color.getG()*ambiantReflection;
  
  for(DirectionalLight l : lights) {
    g += color.getG()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    g += color.getG()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
		shininess));
  }
  
  g<255 ? g=g : g=255;


  b += color.getB()*ambiantReflection;
  
  for(DirectionalLight l : lights) {
    b += color.getB()*diffuseReflection*fabs(l.getDirection().scalar(normal));
    b += color.getB()*specularReflection
      *fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), 
		shininess));
  }
  
  b<255 ? b=b : b=255;

  //    Logger::log(LOG_DEBUG)<< r << " " << g << " " << b <<endl;  
    return Color(r, g, b);

}
