#include "phongMaterial.hpp"
#include "logger.hpp"
#include "settings.hpp"
#include "directionalLight.hpp"
#include <cmath>
#include "scene.hpp"


PhongMaterial::PhongMaterial(const Color &color, 
			     float specularReflection, 
			     float diffuseReflection, 
			     float ambiantReflection, 
			     float shininess,
			     float reflectivity,
			     int maxReflections,
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
    maxReflections(maxReflections),
    transparency(transparency),
    refractiveIn(refractiveIn),
    refractiveOut(refractiveOut)
{

}

Color PhongMaterial::renderRay(Ray &ray, float distance, const VEC3F &normal, Scene *scene) {

    float r = 0;
    float g = 0;
    float b = 0;
  
    VEC3F rayDirection = ray.getDirection();

    VEC3F lightDirection;

    VEC3F point = ray.getOrigin() + ray.getDirection()*distance;
    list<Light *> lights = scene->visibleLights(point, 0);
    //    list<Light*> lights = scene->getLights();
  

    float diffuse;
    float specular;
  
    Color ambientColor = (scene->getAmbientLight()).getColor();

    float rr;
    float rg;
    float rb;

    float exposure = 1;
  
    r += color.getR()*ambiantReflection*ambientColor.getR();
    g += color.getG()*ambiantReflection*ambientColor.getG();
    b += color.getB()*ambiantReflection*ambientColor.getB();

    list<Light *>::iterator itLight;



    for (itLight = lights.begin(); itLight != lights.end(); itLight++) {

    //lightDirection = itLight->getDirection();
    lightDirection = (*itLight)->getDirection(point);
	    
	    diffuse = diffuseReflection*fabs(lightDirection.scalar(normal));
	    specular = specularReflection*fabs(pow(lightDirection.symmetry(normal).scalar(rayDirection*(-1)), shininess));

	    rr = (*itLight)->getColor().getR();
	    rg = (*itLight)->getColor().getG();
	    rb = (*itLight)->getColor().getB();

	    r += color.getR()*diffuse*rr;
	    g += color.getG()*diffuse*rg;
	    b += color.getB()*diffuse*rb;

	    r += color.getR()*specular*rr;
	    g += color.getG()*specular*rg;
	    b += color.getB()*specular*rb;
 
	}

    Color black = Color(0,0,0);

    if(reflectivity != 0 && ray.reflections < maxReflections) {
	ray.reflections += 1;

	Ray reflectedRay = Ray(point,
			       (rayDirection*(-1)).symmetry(normal),
			       black,
			       ray.reflections);

	Color reflectedColor = scene->renderRay(reflectedRay);

	r += reflectivity*/*color.getR()**/reflectedColor.getR();
	g += reflectivity*/*color.getG()**/reflectedColor.getG();
	b += reflectivity*/*color.getB()**/reflectedColor.getB();

    }


    if(transparency != 0 && ray.reflections < maxReflections) {
	ray.reflections += 1;

    
	float n;
	float cosI;
	float sinI2;    
	VEC3F direction;
	VEC3F normalol = VEC3F(normal);
    
	if(normal.scalar(rayDirection) < 0) {
	    n = refractiveIn/refractiveOut;

	    cosI = rayDirection.scalar(normal);
	    sinI2 = 1-cosI*cosI;
	    if(sinI2 <= 1) {
		direction = rayDirection*n + normalol*(n*cosI+sqrt(1-n*n*sinI2));
	    }
	} else {
	    n = refractiveOut/refractiveIn;
	    cosI = rayDirection.scalar(normal)*(-1);
	    sinI2 = 1 - cosI*cosI;
	    if(sinI2 <= 1) {
		direction = rayDirection*n + normalol*(-n*cosI-sqrt(1-n*n*sinI2));
	    }
	}

	Ray refractedRay = ray;

	if(sinI2 <= 1) {

	    refractedRay = Ray(point+direction*0.1,
			       direction,
			       black,
			       ray.reflections);
	} else {
	    refractedRay = Ray(point,
			       (rayDirection*(-1)).symmetry(normal),
			       black,
			       ray.reflections);
      

	}
	Color refractedColor = scene->renderRay(refractedRay);
      
	r += transparency*color.getR()*refractedColor.getR();
	g += transparency*color.getG()*refractedColor.getG();
	b += transparency*color.getB()*refractedColor.getB();
    
    }
  
    // We are taking care of the exposure in order to avoid the min function

    float expp = expf(exposure*r);
    float expm = expf(-exposure*r);

    r = (expp - expm)/(expp + expm);

    expp = expf(exposure*g);
    expm = expf(-exposure*g);

    g = (expp - expm)/(expp + expm);

    expp = expf(exposure*b);
    expm = expf(-exposure*b);

    b = (expp - expm)/(expp + expm);

    // if(r>1) {
    // 	Logger::log(LOG_INFO) << "r out of bounds" << std::endl;
    // 	r=1;
    // }
    // if(g>1) {
    // 	Logger::log(LOG_INFO) << "g out of bounds" << std::endl;
    // 	g=1;
    // }
    // if(b>1) {
    // 	Logger::log(LOG_INFO) << "b out of bounds" << std::endl;
    // 	b=1;
    // }  

    return Color(r, g, b);

}
