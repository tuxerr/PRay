#include "object.h"

#include "material.h"

Object::Object(Material* material) :
  material(material)
{

}

// to avoid linking problem
//
// => But the virtual wasn't here to show off ...
int Object::getIntersection(Ray& ray, 
                            float* distance, 
                            Vec4<float>* normal, 
                            Material* material) {
    return 0;
}

Material Object::getMaterial() {
  return *material;
}
