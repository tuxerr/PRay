#ifndef DEF_SCENE
#define DEF_SCENE

#include <list>

#include "vec3.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "ambientLight.hpp"
#include "directionalLight.hpp"
#include "ray.hpp"
#include "object.hpp"


using namespace std;

class Material;

class Scene {
private :
    list<Object*> objects;
    list<Light*> lights;
    AmbientLight ambientLight;
    Camera* camera;
public :
    Scene(const list<Object*> objects,
	  const list<Light*> lights,
	  const AmbientLight& ambientLight,
	  Camera* camera);
    ~Scene();
    list<Object*> getObjects();
    list<Light*> getLights();
    AmbientLight getAmbientLight();
    Camera* getCamera();
    Color renderRay(Ray &ray);
    void computeIntersection(Ray &ray, float *distance, VEC3F *normal,
			     Material **material);
    Color renderPixel(int x, int y);
    list<Light *> visibleLights(VEC3F point, float intensity);
};

#endif
