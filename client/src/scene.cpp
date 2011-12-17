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
  Material* material = 0;

  computeDistance(ray, &distance, &normal, &material);

  if (distance < 0) {
    return Color(0,0,0);
  } else {
    return Color(100,40,200); // to prevent from the following segmentation fault
    Color color = material->renderRay(ray, normal, this); 
    // Segmentation fault
    // - Jump to the an invalid address
    //   Address is not stack'd, malloc'd or (recently) free'd
    // - Use of uninitialised value of size 4
    //   Uninitialised value was created by a stack allocation in Scene::renderPixel
    return color;
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeDistance(Ray &ray, float *distance, Vec4<float> *normal, 
                            Material **material) {
    
    *distance = -2;
    float tempDistance = -1;
    list<Object*>::iterator iter;

    for (iter = objects.begin(); iter != objects.end(); iter++) {
        (*iter)->getIntersection(ray, &tempDistance, normal, material);
        if (tempDistance >= 0 
	    && ((*distance >= 0 && tempDistance < *distance) 
		|| *distance < 0 ))
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
