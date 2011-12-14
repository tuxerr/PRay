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
  try { 
    getIntersection(ray, &distance, &normal, &material);
    return material.renderRay(ray, normal, this);
  } catch (int e) {
      if(e != NO_INTERSECTION) {
	throw e;
      } else {
	return Color(0,0,0);
      }
  }
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


Color Scene::renderPixel(int x, int y) {
  
  Vec4<float> vector = camera.getDirection(x, y).normalize();
  Color color = Color(1,1,1);
  Vec4<float> point = camera.getPoint().normalize();
  Ray r = Ray(point, vector, color);
  return renderRay(r);
}
