#include "scene.h"

Scene::Scene(list<Object> objects, list<DirectionalLight> directionalLights, AmbientLight ambientLight) :
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

Intersection Scene::getIntersection(Ray ray) {
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
