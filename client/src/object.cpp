#include "object.h"
#include "logger.h"
#include "material.h"

Object::Object(Material* material) :
  material(material)
{

}

// to avoid linking problem
int Object::getIntersection(Ray& ray, 
                            float* distance, 
                            Vec4<float>* normal, 
                            Material* material) {
    
    Logger::log(LOG_ERROR)<<"Object::getIntersection(...) should not be called"<<endl;

    return 0;
}

Material Object::getMaterial() {
  return *material;
}
