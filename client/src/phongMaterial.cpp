#include "phongMaterial.hpp"
#include "logger.hpp"
#include "directionalLight.hpp"
#include "math.h"
#include "scene.hpp"

#define MAX_REFLECTIONS 20

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
  reflectivity(1),
  transparency(0),
  refractiveIn(1),
  refractiveOut(1)
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
  refractiveOut(refractiveOut)
{

}

Color PhongMaterial::renderRay2(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) {

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

  if(reflectivity != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;

    Ray reflectedRay = Ray(point,
			   (rayDirection*(-1)).symmetry(normal),
			   black);

    Color reflectedColor = scene->renderRay(reflectedRay);

    r += reflectivity*color.getR()*reflectedColor.getR();
    g += reflectivity*color.getG()*reflectedColor.getG();
    b += reflectivity*color.getB()*reflectedColor.getB();

  }


  if(transparency != 0 && scene->reflections < MAX_REFLECTIONS) {
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
    //    Logger::log(LOG_DEBUG) << "coef!!! = " << (n*cosI+sqrt(1-n*n*sinI2)) << endl;
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



Vec3<float> PhongMaterial::reflect(Vec3<float> normal, Vec3<float> incident) {
  float cosI = -(normal.scalar(incident));
  return incident + normal*(2*cosI);
}

Vec3<float> PhongMaterial::refract(Vec3<float> normal, Vec3<float> incident, 
				   float n1, float n2) {
  float cosT;
  float n = n1/n2;
  float cosI = -(normal.scalar(incident));
  float sinT2 = n*n*(1.0 - cosI*cosI);
  if(sinT2 > 1.0) {
    return NULL;
  } else {
    cosT = sqrt(1 - sinT2);
    return incident*n + normal*(n*cosI - cosT);
  }
}


float PhongMaterial::reflectance(Vec3<float> normal, Vec3<float> incident,
				 float n1, float n2) {

  float n = n1/n2;
  float cosI = -(normal.scalar(incident));
  float sinT2 = n*n*(1.0 - cosI*cosI);
  if(sinT2 > 1.0) {
    return 1.0;
  } else {
    float cosT = sqrt(1 - sinT2);
    float rOrth = (n1*cosI - n2*cosT)/(n1*cosI + n2*cosT);
    float rPar = (n2*cosI - n1*cosT)/(n2*cosI + n1*cosT);
    return (rOrth*rOrth + rPar*rPar)/2.0;
  }
}


float PhongMaterial::rSchlick2(Vec3<float> normal, Vec3<float> incident,
			       float n1, float n2) {

  float r0 = (n1 - n2)/(n1 + n2);
  r0 *= r0;
  float cosI = -(normal.scalar(incident));
  float n;
  float sinT2;
  float cosX;
  if(n1 > n2) {
    n = n1/n2;
    sinT2 = n*n*(1.0 - cosI*cosI);
    if(sinT2 > 1.0) {
      return 1.0;
    } else {
      cosX = sqrt(1.0 - sinT2);
    }
    float x = 1.0 - cosX;
    return r0 + (1.0 - r0)*x*x*x*x;
  } else {
    return 1;
  }
}


Color PhongMaterial::renderRay(const Ray &ray, float distance, const Vec3<float> &normal, Scene *scene) {

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

  if(reflectivity != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;

    Vec3<float> reflected = reflect(normal, rayDirection);

    Ray reflectedRay = Ray(point,
			   reflected,
			   black);
  
    Color reflectedColor = scene->renderRay(reflectedRay);
  
    r += reflectivity*color.getR()*reflectedColor.getR();//*reflectance(normal, rayDirection, refractiveOut, refractiveIn);
    g += reflectivity*color.getG()*reflectedColor.getG();//*reflectance(normal, rayDirection, refractiveOut, refractiveIn);
    b += reflectivity*color.getB()*reflectedColor.getB();//*reflectance(normal, rayDirection, refractiveOut, refractiveIn);

  }


  if(transparency != 0 && scene->reflections < MAX_REFLECTIONS) {
    scene->reflections += 1;

    Vec3<float> refracted = refract(normal, rayDirection, refractiveOut, refractiveIn);  

    Ray refractedRay = Ray(point+refracted*0.01,
			   refracted,
			   black);
  
    Color refractedColor = scene->renderRay(refractedRay);

    Logger::log(LOG_DEBUG) << "rayDirection = " 
			   << rayDirection.x
			   << rayDirection.y 
			   << rayDirection.z << endl;

    Logger::log(LOG_DEBUG) << "direction = " 
			   << refracted.x
			   << refracted.y 
			   << refracted.z << endl;

    //  r += transparency*color.getR()*refractedColor.getR()*rSchlick2(normal, rayDirection, refractiveOut, refractiveIn);
    //  g += transparency*color.getG()*refractedColor.getG()*rSchlick2(normal, rayDirection, refractiveOut, refractiveIn);
    //  b += transparency*color.getB()*refractedColor.getB()*rSchlick2(normal, rayDirection, refractiveOut, refractiveIn);

  }
  
  /*

    Logger::log(LOG_DEBUG) << "rayDirection = " 
    << rayDirection.x
    << rayDirection.y 
    << rayDirection.z << endl;

    Logger::log(LOG_DEBUG) << "direction = " 
    << refracted.x
    << refracted.y 
    << refracted.z << endl;

  */



  

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
