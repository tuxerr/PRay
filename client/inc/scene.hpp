#ifndef DEF_SCENE
#define DEF_SCENE

#include <list>
#include <cfloat>

#include "vec3.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "ambientLight.hpp"
#include "directionalLight.hpp"
#include "ray.hpp"
#include "object.hpp"
#include "logger.hpp"
#include "material.hpp"
#include "uglyMaterial.hpp"
#include "settings.hpp"
#include "kdtree.hpp"
#include "aabb.hpp"

using namespace std;

class Material;

class Scene {
private :
    list<Object*> objects;
    list<Light*> lights;
    AmbientLight ambientLight;
    Camera* camera;
    KdTreeNode* kdTree;
    AABB* computeGlobalAABB();
    void computeKdTree(); 
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
    KdTreeNode* getKdTree();
    Color renderRay(Ray &ray);
    void computeIntersection(Ray &ray, float *distance, VEC3F *normal,
			     Material **material);
    Color renderPixel(int x, int y);
    list<Light *> visibleLights(VEC3F point, float intensity);
};

#endif
