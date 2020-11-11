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

Color PhongMaterial::renderRay(Ray &ray, float distance, const VEC3F &normal, Scene *scene) {

    
    float r = 0;
    float g = 0;
    float b = 0;
  


    VEC3F point = ray.origin + ray.direction*distance;
    list<Light *> lights = scene->visibleLights(point, 0);
    //    list<Light*> lights = scene->getLights();
  


  
    Color ambientColor = (scene->getAmbientLight()).getColor();
  
    r += color.getR()*ambiantReflection*ambientColor.getR();
    g += color.getG()*ambiantReflection*ambientColor.getG();
    b += color.getB()*ambiantReflection*ambientColor.getB();



    list<Light *>::iterator itLight;

    VEC3F rayDirection = ray.direction;
    VEC3F lightDirection;
    float diffuse;
    float specular;
    float rr;
    float rg;
    float rb;

    for (itLight = lights.begin(); itLight != lights.end(); itLight++) {

	//lightDirection = itLight->getDirection();
	lightDirection = (*itLight)->getDirection(point);
	    
	diffuse = diffuseReflection*fabs(lightDirection.scalar(normal));
	specular = specularReflection*
	    fabs(pow(lightDirection.symmetry(normal).
		     scalar(rayDirection*(-1)), shininess));

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

    addReflection(r, g, b, ray, point, normal, scene);
    addRefraction(r, g, b, ray, point, normal, scene);
    


    // We are taking care of the exposure in order to avoid the min function
    // Instead of taking the min between the colors and 1, we are applying
    // the fonction th to the colors.

    float exposure = Settings::getAsFloat("exposure");

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
    // 	r=1;
    // }
    // if(g>1) {
    // 	g=1;
    // }
    // if(b>1) {
    // 	b=1;
    // }  

    return Color(r, g, b);

}

void PhongMaterial::addReflection(float &r, float &g, float &b,
				  Ray &ray, VEC3F &point,
				  const VEC3F &normal, Scene *scene) {

    if(reflectivity != 0 && ray.reflections < Settings::getAsInt("max_reflections")) {
	ray.reflections += 1;

	Color black = Color(0,0,0);
	
	Ray reflectedRay = Ray(point,
			       (ray.direction*(-1)).symmetry(normal),
			       black,
			       ray.reflections);

	Color reflectedColor = scene->renderRay(reflectedRay);

	r += reflectivity*/*color.getR()**/reflectedColor.getR();
	g += reflectivity*/*color.getG()**/reflectedColor.getG();
	b += reflectivity*/*color.getB()**/reflectedColor.getB();

    }
}

void PhongMaterial::addRefraction(float &r, float &g, float &b,
				  Ray &ray, VEC3F &point,
				  const VEC3F &normal, Scene *scene) {


    if(transparency != 0 && ray.reflections < Settings::getAsInt("max_reflections")) {
	ray.reflections += 1;

    
	float n;
	float cosI;
	float sinI2;    
	VEC3F direction;
	VEC3F rayDirection = ray.direction;
	VEC3F normalol = VEC3F(normal);
	Color black = Color(0,0,0);    

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
}
