#include "phongMaterial.hpp"
#include "logger.hpp"
#include "settings.hpp"
#include "directionalLight.hpp"
#include "math.h"
#include "scene.hpp"

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
  reflectivity(reflectivity),
  transparency(0),
  refractiveIn(1.05),
  refractiveOut(1),
  max_reflections(Settings::getAsInt("max_reflections"))
{

}

PhongMaterial::PhongMaterial(const Color &color, 
			     float specularReflection, 
			     float diffuseReflection, 
			     float ambiantReflection, 
			     float shininess,
			     float reflectivity,
			     float transparency,
			     float refractiveIn,
			     float refractiveOut
			     ):
  color(color), 
  specularReflection(specularReflection), 
  diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), 
  shininess(shininess),
  reflectivity(reflectivity),
  transparency(transparency),
  refractiveIn(refractiveIn),
  refractiveOut(refractiveOut),
  max_reflections(Settings::getAsInt("max_reflections"))
{

}

Color PhongMaterial::renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) {

  //  Logger::log(LOG_DEBUG) << "PHONG " << endl;

  float r = 0;
  float g = 0;
  float b = 0;

  Vec3<float> rayDirection = ray.getDirection();

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
      specular = specularReflection*fabs(pow(itLight->getDirection().symmetry(normal).scalar(rayDirection*(-1)), shininess));

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

  if(reflectivity != 0 && scene->reflections < max_reflections) {
    scene->reflections += 1;

    Ray reflectedRay = Ray(point,
			   (rayDirection*(-1)).symmetry(normal),
			   black);

    Color reflectedColor = scene->renderRay(reflectedRay);

    r += reflectivity*color.getR()*reflectedColor.getR();
    g += reflectivity*color.getG()*reflectedColor.getG();
    b += reflectivity*color.getB()*reflectedColor.getB();

  }


  if(transparency != 0 && scene->reflections < max_reflections) {
    scene->reflections += 1;

    
    float n;
    float cosI;
    float sinI2;    
    Vec3<float> direction;
    Vec3<float> normalol = Vec3<float>(normal);
    
    if(normal.scalar(rayDirection) < 0) {
      n = refractiveIn/refractiveOut;

      cosI = rayDirection.scalar(normal);
      sinI2 = 1-cosI*cosI;
      if(sinI2 <= 1) {
	direction = rayDirection*n + normalol*(n*cosI+sqrt(1-n*n*sinI2));
	//	Logger::log(LOG_DEBUG) << "coef = " << (-n*cosI+sqrt(1-n*n*sinI2)) << endl;
      }
    } else {
      n = refractiveOut/refractiveIn;
      cosI = rayDirection.scalar(normal)*(-1);
      sinI2 = 1 - cosI*cosI;
      if(sinI2 <= 1) {
	direction = rayDirection*n + normalol*(-n*cosI-sqrt(1-n*n*sinI2));
	//	Logger::log(LOG_DEBUG) << "coef = " << (n*cosI-sqrt(1-n*n*sinI2)) << endl;
      }
    }

    //    Logger::log(LOG_DEBUG) << "n = " << n << endl;
    //    Logger::log(LOG_DEBUG) << "cosI = " << cosI << " ou " << sqrt(1-n*n*sinI2)<<  endl;
    //    Logger::log(LOG_DEBUG) << "coef!!! = " << (n*cosI-sqrt(1-n*n*sinI2)) << endl;
    Ray refractedRay = ray;

    if(sinI2 <= 1) {
      /*
	Logger::log(LOG_DEBUG) << "rayDirection = " 
	<< rayDirection.x
	<< rayDirection.y 
	<< rayDirection.z << endl;
	
	
	Logger::log(LOG_DEBUG) << "direction = " 
	<< direction.x
	<< direction.y 
	<< direction.z << endl;
      */  
      refractedRay = Ray(point+direction*0.1,
			 direction,
			 black);
    } else {
      refractedRay = Ray(point,
			 (rayDirection*(-1)).symmetry(normal),
			 black);
      

    }
    Color refractedColor = scene->renderRay(refractedRay);
      
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
