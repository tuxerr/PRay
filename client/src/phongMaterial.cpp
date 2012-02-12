#include "phongMaterial.h"
#include "logger.h"
#include "directionalLight.h"
#include "math.h"
#include "scene.h"

#define MAX_REFLECTIONS 10

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
  reflectivity(1)
{

}

PhongMaterial::PhongMaterial(const Color &color, 
			     float specularReflection, 
			     float diffuseReflection, 
			     float ambiantReflection, 
			     float shininess,
			     float reflectivity,
			     float transparency,
			     float refractionIndice) :
  color(color), 
  specularReflection(specularReflection), 
  diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), 
  shininess(shininess),
  reflectivity(reflectivity),
  transparency(1),
  refractionIndice(2.419)
{

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

  list<DirectionalLight>::iterator itLight;
  
  for (itLight = lights.begin(); itLight != lights.end(); itLight++)
  {

    diffuse = diffuseReflection*fabs(itLight->getDirection().scalar(normal));
    specular = specularReflection*fabs(pow(itLight->getDirection().symmetry(normal).scalar(ray.getDirection()*(-1)), shininess));

    rr = itLight->getColor().getR();
    rg = itLight->getColor().getG();
    rb = itLight->getColor().getB();

    r += color.getR()*diffuse*rr;
    g += color.getG()*diffuse*rg;
    b += color.getB()*diffuse*rb;

    r += color.getR()*specular*rr;
    g += color.getG()*specular*rg;
    b += color.getB()*specular*rb;
 
  }

    Color black = Color(0,0,0);

  if(reflectivity != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;

    Ray reflectedRay = Ray(point,
			   (ray.getDirection()*(-1)).symmetry(normal),
			   black);

    Color reflectedColor = scene->renderRay(reflectedRay);

    r += reflectivity*color.getR()*reflectedColor.getR();
    g += reflectivity*color.getG()*reflectedColor.getG();
    b += reflectivity*color.getB()*reflectedColor.getB();

  }


  if(false && transparency != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;

    

    Ray reflectedRay = Ray(point,
			   (ray.getDirection()*(-1)).symmetry(normal),
			   black);

    Color refractedColor = scene->renderRay(reflectedRay);

    r += transparency*color.getR()*refractedColor.getR();
    g += transparency*color.getG()*refractedColor.getG();
    b += transparency*color.getB()*refractedColor.getB();

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
