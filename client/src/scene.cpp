#include "logger.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "uglyMaterial.hpp"
#include "settings.hpp"

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
  VEC3F normal;
  Material* material = 0;

  computeIntersection(ray, &distance, &normal, &material);

  if (distance < 0) { // no intersection was found
    //    Logger::log(LOG_DEBUG) << "NO INTERSECTION" << endl;
    return Color(0,0,0);
  } else {
    /*    Logger::log(LOG_DEBUG) << "INTERSECTION : " << material << endl;
    Logger::log(LOG_DEBUG) << "TROLOL" << endl;
    
    
    Logger::log(LOG_DEBUG) << "ray : " << &ray << endl;
    Logger::log(LOG_DEBUG) << "distance : " << &distance << endl;
    Logger::log(LOG_DEBUG) << "normal : " << &normal << endl;
    Logger::log(LOG_DEBUG) << "this : " << this << endl;*/
    return material->renderRay(ray, distance, normal, this);
  }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeIntersection(Ray &ray, float *distance, VEC3F *normal,
                                Material **material) {

    *distance = -2;
    float tempDistance = -1;
    VEC3F tempNormal;
    Material* tempMaterial;
    list<Object*>::iterator iter;

    for (iter = objects.begin(); iter != objects.end(); iter++)
    {
        (*iter)->getIntersection(ray, &tempDistance, &tempNormal, &tempMaterial);

	// Fixes the precision problem for shadows.
	if(tempDistance < 0 && tempDistance > -0.001) {
	  tempDistance = -tempDistance;
      	}
	// ----------------------------------------


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
    
    int launchedRays = 0;
    VEC3F origin = camera->getPoint();
    std::vector<VEC3F> directions;
    std::vector<Color> colors;
    float mean_r=0, mean_g=0, mean_b=0;
    float old_mean_r, old_mean_g, old_mean_b;

    directions = camera->getFourDirections(x, y);
    for (int i = 0 ; i < 4 ; i++) {
        Color color;
        Ray ray = Ray(origin, directions[i], color);
        Color res = renderRay(ray);
        launchedRays++;
        colors.push_back(res);
        mean_r += res.getR();
        mean_g += res.getG();
        mean_b += res.getB();
    }
    mean_r /= 4;
    mean_g /= 4;
    mean_b /= 4;

    bool doSupersampling = false;

    for (int i = 0 ; i < 4 ; i++) {
        if (fabs(mean_r - colors[i].getR())
            + fabs(mean_g - colors[i].getG())
            + fabs(mean_b - colors[i].getB()) 
            > Settings::getAsFloat("supersampling_threshold_start")) {
            doSupersampling = true;
            break;
        }
    }

    if (doSupersampling) {
        do {
            old_mean_r = mean_r;
            old_mean_g = mean_g; 
            old_mean_b = mean_b;

            mean_r *= launchedRays;
            mean_g *= launchedRays;
            mean_b *= launchedRays;

            directions.clear();
            directions = camera->getFourDirections(x, y);
            for (int i = 0 ; i < 4 ; i++) {
                Color color;
                Ray ray = Ray(origin, directions[i], color);
                Color res = renderRay(ray);
                launchedRays++;
                mean_r += res.getR();
                mean_g += res.getG();
                mean_b += res.getB();
            }

            mean_r /= launchedRays;
            mean_g /= launchedRays;
            mean_b /= launchedRays;

        } while ((launchedRays < Settings::getAsInt("supersampling_max_rays"))
                 && (fabs(old_mean_r - mean_r)
                     + fabs(old_mean_g - mean_g)
                     + fabs(old_mean_b - mean_b)
                     > Settings::getAsFloat("supersampling_threshold_end")));
    }
/*
    if (launchedRays > 4) {
        Logger::log(LOG_DEBUG)<<"launchedRays="<<launchedRays<<endl;
    }
*/
    if (Settings::getAsBool("supersampling_show")) {
        return Color(min((float)1.0, (float)(launchedRays - 4) 
                         / Settings::getAsFloat("supersampling_show_limit")));
    } else {
        return Color(mean_r, mean_g, mean_b);
    }
}

/**
 * Give the lights that are visible from a point. Used for shadows.
 */
list<DirectionalLight> Scene::visibleLights(VEC3F point) {

  float distance = -1;
  VEC3F normal;
  Material *material;
  Color color = Color(0.0);
  list<DirectionalLight> result;
  Ray ray = Ray(point, normal, color);

  list<DirectionalLight>::iterator itLight;
  
  for (itLight = directionalLights.begin(); itLight != directionalLights.end(); itLight++)
  {
      ray = Ray(point, itLight->getDirection()*(-1), color);
      computeIntersection(ray, &distance, &normal, &material);
      //  Logger::log(LOG_DEBUG)<< distance <<endl;      
      if(distance < 0) {
          result.push_back(*itLight);
      }
  }

  return result;
}
