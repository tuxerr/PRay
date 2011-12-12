#ifndef DEF_SCENE
#define DEF_SCENE

#include "object.h"
#include "ambientLight.h"
#include "directionalLight.h"
#include "intersection.h"
#include "ray.h"
#include <list>
#include "vec4.h"

using namespace std;

class Scene {

 private :
  list<Object> objects;
  list<DirectionalLight> directionalLights;
  AmbientLight ambientLight;
 public :
  Scene(const list<Object> &objects, const list<DirectionalLight> &directionalLights, const AmbientLight &ambientLight);
  list<Object> getObjects();
  list<DirectionalLight> getDirectionalLights();
  AmbientLight getAmbientLight();
  Color renderRay(const Ray &ray);
  Intersection getIntersection(const Ray &ray);
};

#endif
