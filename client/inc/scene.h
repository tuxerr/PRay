#ifndef DEF_SCENE
#define DEF_SCENE

#include "object.h"
#include "ambientLight.h"
#include "directionalLight.h"
#include "intersection.h"
#include "ray.h"
#include <list>

using namespace std;

class Scene {

 private :
  list<Object> objects;
  list<DirectionalLight> directionalLights;
  AmbientLight ambientLight;
 public :
  Scene(list<Object> objects, list<DirectionalLight> directionalLights, AmbientLight ambientLight);
  list<Object> getObjects();
  list<DirectionalLight> getDirectionalLights();
  AmbientLight getAmbientLight();
  Intersection getIntersection(Ray ray);
};

#endif
