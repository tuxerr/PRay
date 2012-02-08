#include "logger.h"
#include "scene.h"
#include "material.h"
#include "uglyMaterial.h"

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
  Vec3<float> normal;
  Material* material = 0;

  computeIntersection(ray, &distance, &normal, &material);

  if (distance < 0) { // no intersection was found
    //    Logger::log(LOG_DEBUG) << "NO INTERSECTION" << endl;
    return Color(0,0,0);
  } else {
    //    Logger::log(LOG_DEBUG) << "INTERSECTION : " << material << endl;
    return material->renderRay(ray, distance, normal, this);
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeIntersection(Ray &ray, float *distance, Vec3<float> *normal,
                                Material **material) {

    *distance = -2;
    float tempDistance = -1;
    Vec3<float> tempNormal;
    Material* tempMaterial;
    list<Object*>::iterator iter;

    for (iter = objects.begin(); iter != objects.end(); iter++)
    {
        (*iter)->getIntersection(ray, &tempDistance, &tempNormal, &tempMaterial);

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

    Vec3<float> direction  = camera->getDirection(x, y); //.normalize();
    Color color = Color(0,0,0);
    Vec3<float> origin = camera->getPoint();
    Ray r = Ray(origin, direction, color);
    //    Logger::log(LOG_DEBUG) << "before scene::renderRay" << endl;
    return renderRay(r);
}

/**
 * Give the lights that are visible from a point. Used for shadows.
 */
list<DirectionalLight> Scene::visibleLights(Vec3<float> point) {

  float distance = -1;
  Vec3<float> normal;
  Material *material = new UglyMaterial(Color(255, 127, 0));
  Color color = Color(0.0);
  list<DirectionalLight> result = list<DirectionalLight>();
  Ray ray = Ray(point, normal, color);

  for(DirectionalLight l : directionalLights) {
    ray = Ray(point, l.getDirection()*(-1), color);
    computeIntersection(ray, &distance, &normal, &material);
    if(distance <= 0) {
      result.push_back(l);
    }
  }

  //  delete material;
  return result;
}
