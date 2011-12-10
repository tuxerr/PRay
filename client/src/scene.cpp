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
  return AmbientLight;
}

Intersection Scene::getIntesection(Ray ray) {
  List<Object>::iterator iter = objects.begin();
  Intersection result;
  Intersection candidate;
  for(iter = objects.begin(); iter != objects.end(); i++) {
    try {
      candidate = (* iter).getInstersection(ray);
      if(candidate.getDistance() < result.getDistance) {
	result = candidate;
      }
    } catch(int e) {
      if(e != NO_INTERSECTION) {
	throw e;
      }
    }
  }
}
