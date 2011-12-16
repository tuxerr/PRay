#include "logger.h"
#include "scene.h"
#include "material.h"

Scene::Scene(const list<Object> &objects,
	     const list<DirectionalLight> &directionalLights,
	     const AmbientLight &ambientLight,
	     const Camera &camera) :
  objects(objects),
  directionalLights(directionalLights),
  ambientLight(ambientLight),
  camera(camera)
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
  
  if (distance < 0) {
      return Color(0,0,0);
  } else {
      return material.renderRay(ray, normal, this);
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::getIntersection(Ray &ray, float *distance, Vec4<float> *normal, 
                            Material *material) {
    
    *distance = -1;
    float tempDistance = -1;
    int res;
    list<Object>::iterator iter;
    /* it seems that the list prevent us from using polymorphism */

    for (iter = objects.begin(); iter != objects.end(); iter++) {
        iter->getIntersection(ray, &tempDistance, normal, material);
        if (0 <= tempDistance && tempDistance < *distance) 
            *distance = tempDistance;
    }
}


Color Scene::renderPixel(int x, int y) {
  
    Vec4<float> direction  = camera.getDirection(x, y).normalize();
    Color color = Color(0,0,0);
    Vec4<float> origin = camera.getPoint();
    Ray r = Ray(origin, direction, color);
    return renderRay(r);
}
