#include "logger.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "uglyMaterial.hpp"
#include "settings.hpp"

Scene::Scene(const list<Object*> objects,
	     const list<DirectionalLight> &directionalLights,
	     const AmbientLight &ambientLight,
	     Camera* camera) :
  objects(objects),
  directionalLights(directionalLights),
  ambientLight(ambientLight),
  camera(camera)
{

}

Scene::~Scene()
{
    list<Object*>::iterator iter;

    for (iter = objects.begin() ; iter != objects.end() ; iter++) {
        delete *iter;
    }

    //delete camera;
}

list<Object*> Scene::getObjects() {
  return objects;
}

list<DirectionalLight> Scene::getDirectionalLights() {
  return directionalLights;
}

AmbientLight Scene::getAmbientLight() {
  return ambientLight;
}

Camera* Scene::getCamera() {
  return camera;
}

Color Scene::renderRay(Ray &ray) {
  float distance;
  VEC3F normal;
  Material* material = 0;

  computeIntersection(ray, &distance, &normal, &material);

  if (distance < 0) { // no intersection was found
    //    Logger::log(LOG_DEBUG) << "NO INTERSECTION" << endl;
    return Color(0,0,0);
  } else {
    /*    Logger::log(LOG_DEBUG) << "INTERSECTION : " << material << endl;
    Logger::log(LOG_DEBUG) << "TROLOL" << endl;
    
    
    Logger::log(LOG_DEBUG) << "ray : " << &ray << endl;
    Logger::log(LOG_DEBUG) << "distance : " << &distance << endl;
    Logger::log(LOG_DEBUG) << "normal : " << &normal << endl;
    Logger::log(LOG_DEBUG) << "this : " << this << endl;*/
    return material->renderRay(ray, distance, normal, this);
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeIntersection(Ray &ray, float *distance, VEC3F *normal,
                                Material **material) {

    *distance = -2;
    float tempDistance = -1;
    VEC3F tempNormal;
    Material* tempMaterial;
    list<Object*>::iterator iter;

    for (iter = objects.begin(); iter != objects.end(); iter++)
    {
        (*iter)->getIntersection(ray, &tempDistance, &tempNormal, &tempMaterial);

	// Fixes the precision problem for shadows.
	if(tempDistance < 0 && tempDistance > -0.001) {
	  tempDistance = -tempDistance;
      	}
	// ----------------------------------------


        if (tempDistance >= 0
            && ((*distance >= 0 && tempDistance < *distance)
                || *distance < 0 ))
        {
            *distance = tempDistance;
            *normal = tempNormal;
            *material = tempMaterial;
        }

        tempDistance = -1;
    }
    
}


Color Scene::renderPixel(int x, int y) {
    
    float r=0, g=0, b=0;

    VEC3F origin = camera->getPoint();
    std::list<VEC3F> directions = camera->getDirections(x, y, Settings::getAsInt("sampling"));
    std::list<VEC3F>::iterator iterDir;
    
    for (iterDir = directions.begin() ; iterDir != directions.end() ; iterDir++) {
        Color color;
        Ray ray = Ray(origin, *iterDir, color);
        Color res = renderRay(ray);
        r += res.getR();
        g += res.getG();
        b += res.getB();
    }
    
    int n = directions.size();

    return Color(r/n, g/n, b/n);
}

/**
 * Give the lights that are visible from a point. Used for shadows.
 */
list<DirectionalLight> Scene::visibleLights(VEC3F point) {

  float distance = -1;
  VEC3F normal;
  Material *material;
  Color color = Color(0.0);
  list<DirectionalLight> result;
  Ray ray = Ray(point, normal, color);

  list<DirectionalLight>::iterator itLight;
  
  for (itLight = directionalLights.begin(); itLight != directionalLights.end(); itLight++)
  {
      ray = Ray(point, itLight->getDirection()*(-1), color);
      computeIntersection(ray, &distance, &normal, &material);
      //  Logger::log(LOG_DEBUG)<< distance <<endl;      
      if(distance < 0) {
          result.push_back(*itLight);
      }
  }

  return result;
}
