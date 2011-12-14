#include "object.h"

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
    return 0;
}

Material Object::getMaterial() {
  return *material;
}
