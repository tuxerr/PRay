#include "logger.h"
#include "scene.h"
#include "material.h"

Scene::Scene(const list<Object*> objects,
	     const list<DirectionalLight> &directionalLights,
	     const AmbientLight &ambientLight,
	     const Camera &camera) :
  objects(objects),
  directionalLights(directionalLights),
  ambientLight(ambientLight),
  camera(camera)
{

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

Camera Scene::getCamera() {
  return camera;
}

Color Scene::renderRay(Ray &ray) {
  float distance;
  Vec4<float> normal;
  Material material;

  computeDistance(ray, &distance, &normal, &material);

  Logger::log()<<"distance="<<distance<<endl;
  
  if (distance < 0) {
    return Color(0,0,0);
  } else {
    Logger::log()<<"Rendering material"<<endl;
    return material.renderRay(ray, normal, this);
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeDistance(Ray &ray, float *distance, Vec4<float> *normal, 
                            Material *material) {
    
    *distance = -2;
    float tempDistance = -1;
    int res;
    list<Object*>::iterator iter;
    /* it seems that the list prevent us from using polymorphism */

    for (iter = objects.begin(); iter != objects.end(); iter++) {
        (*iter)->getIntersection(ray, &tempDistance, normal, material);
        if ((*distance >= 0 && tempDistance >= 0 && tempDistance < *distance) 
	    || tempDistance >= 0)
	  *distance = tempDistance;
    }
}


Color Scene::renderPixel(int x, int y) {
  
    Vec4<float> direction  = camera.getDirection(x, y).normalize();
    Color color = Color();
    Vec4<float> origin = camera.getPoint();
    Ray r = Ray(origin, direction, color);
    return renderRay(r);
}
