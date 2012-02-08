#ifndef DEF_SCENE
#define DEF_SCENE

#include <list>

#include "vec3.h"
#include "camera.h"
#include "color.h"
#include "ambientLight.h"
#include "directionalLight.h"
#include "ray.h"
#include "object.h"


using namespace std;

class Material;

class Scene {
 private :
  list<Object*> objects;
  list<DirectionalLight> directionalLights;
  AmbientLight ambientLight;
  Camera* camera;
 public :
  Scene(const list<Object*> objects,
	const list<DirectionalLight>& directionalLights,
	const AmbientLight& ambientLight,
	Camera* camera);
  ~Scene();
  list<Object*> getObjects();
  list<DirectionalLight> getDirectionalLights();
  AmbientLight getAmbientLight();
  Camera* getCamera();
  Color renderRay(Ray &ray);
  void computeIntersection(Ray &ray, float *distance, Vec3<float> *normal,
                           Material **material);
  Color renderPixel(int x, int y);
  list<DirectionalLight> visibleLights(Vec3<float> point);
};

#endif
