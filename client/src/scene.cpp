#include "scene.h"

#include "material.h"

Scene::Scene(const list<Object> &objects, const list<DirectionalLight> &directionalLights, const AmbientLight &ambientLight, Camera & camera) :
  objects(objects), directionalLights(directionalLights), ambientLight(ambientLight), camera(camera)
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

Camera Scene::getCamera() {
  return camera;
}

Color Scene::renderRay(Ray &ray) {
  float distance;
  Vec4<float> normal;
  Material material;
  getIntersection(ray, &distance, &normal, &material);
  return material.renderRay(ray, normal, this);
}

int Scene::getIntersection(Ray &ray, float *distance, Vec4<float> *normal, Material *material) {
  list<Object>::iterator iter = objects.begin();

  *distance = -1;
  float tempDistance = -1;

  for(iter = objects.begin(); iter != objects.end(); iter++) {
    try {
      (* iter).getIntersection(ray, &tempDistance, normal, material);
      if(tempDistance < *distance || *distance < 0) {
	*distance = tempDistance;
      }
    } catch(int e) {
      if(e != NO_INTERSECTION) {
	throw e;
      }
    }
  }
  if(*distance < 0) {
    throw NO_INTERSECTION;
  }
  return 0;
}
