#include "scene.h"

Scene::Scene(const list<Object> &objects, const list<DirectionalLight> &directionalLights, const AmbientLight &ambientLight) :
  objects(objects), directionalLights(directionalLights), ambientLight(ambientLight)
{

}

list<Object> Scene::getObjects() {
  return objects;
}

list<DirectionalLight> Scene::getDirectionalLights() {
  return directionalLights;
}

AmbientLight Scene::getAmbientLight() {
  return ambientLight;
}

Color Scene::renderRay(const Ray &ray) {
  Intersection inter = getIntersection(ray);
  inter.getMaterial().renderRay(ray, inter.getNormal(), this);
}

Intersection Scene::getIntersection(const Ray &ray) {
  list<Object>::iterator iter = objects.begin();
  Intersection result = (* iter).getIntersection(ray);
  Intersection candidate = (* iter).getIntersection(ray);
  for(iter = objects.begin(); iter != objects.end(); iter++) {
    try {
      candidate = (* iter).getIntersection(ray);
      if(candidate.getDistance() < result.getDistance()) {
	result = candidate;
      }
    } catch(int e) {
      if(e != NO_INTERSECTION) {
	throw e;
      }
    }
  }
}
