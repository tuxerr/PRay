#ifndef DEF_SCENE
#define DEF_SCENE

#include <list>

#include "vec4.h"
#include "camera.h"
#include "color.h"
#include "ambientLight.h"
#include "directionalLight.h"
#include "ray.h"
//#include "material.h"
#include "object.h"


using namespace std;

class Material;

class Scene {
 private :
  list<Object> objects;
  list<DirectionalLight> directionalLights;
  AmbientLight ambientLight;
  Camera camera;
 public :
  Scene(const list<Object>& objects, 
	const list<DirectionalLight>& directionalLights, 
	const AmbientLight& ambientLight, 
	const Camera& camera);
  list<Object> getObjects();
  list<DirectionalLight> getDirectionalLights();
  AmbientLight getAmbientLight();
  Camera getCamera();
  Color renderRay(Ray &ray);
  int getIntersection(Ray &ray, float *distance, Vec4<float> *normal, Material *material);
  Color renderPixel(int x, int y);
};

#endif
