#include "phongMaterial.h"
#include "logger.h"
#include "directionalLight.h"
#include "math.h"
#include "scene.h"

#define MAX_REFLECTIONS 5

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

  //  Logger::log(LOG_DEBUG) << "PHONG " << endl;

  float r = 0;
  float g = 0;
  float b = 0;

  Vec3<float> point = ray.getOrigin() + ray.getDirection()*distance;
  list<DirectionalLight> lights = scene->visibleLights(point);
  //list<DirectionalLight> lights = scene->getDirectionalLights();
  

  float diffuse;
  float specular;
  
  Color ambientColor = (scene->getAmbientLight()).getColor();

  float rr;
  float rg;
  float rb;
  
  r += color.getR()*ambiantReflection*ambientColor.getR();
  g += color.getG()*ambiantReflection*ambientColor.getG();
  b += color.getB()*ambiantReflection*ambientColor.getB();

  for(DirectionalLight l : lights) {

    diffuse = diffuseReflection*fabs(l.getDirection().scalar(normal));
    specular = specularReflection*fabs(pow(l.getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), shininess));

    rr = l.getColor().getR();
    rg = l.getColor().getG();
    rb = l.getColor().getB();

    r += color.getR()*diffuse*rr;
    g += color.getG()*diffuse*rg;
    b += color.getB()*diffuse*rb;

    r += color.getR()*specular*rr;
    g += color.getG()*specular*rg;
    b += color.getB()*specular*rb;
 
  }

  if(reflectivity != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;
    Color black = Color(0,0,0);

    Ray reflectedRay = Ray(point,
			   (ray.getDirection()*(-1)).symmetry(normal),
			   black);

    //    Logger::log(LOG_DEBUG) << "Avant renderRay phong " << scene->reflections << endl;
    //    Logger::log(LOG_DEBUG) << "reflectedRay " << &reflectedRay << endl;
  
    Color reflectedColor = scene->renderRay(reflectedRay);

    //    Logger::log(LOG_DEBUG) << "Color " << reflectedColor.getR() << 
    //      reflectedColor.getG() << 
    //      reflectedColor.getB() << endl;

    r += reflectivity*color.getR()*reflectedColor.getR();
    g += reflectivity*color.getG()*reflectedColor.getG();
    b += reflectivity*color.getB()*reflectedColor.getB();

  }

  if(r>1) {
    r=1;
  }
  if(g>1) {
    g=1;
  }
  if(b>1) {
    b=1;
  }  

  return Color(r, g, b);

}
