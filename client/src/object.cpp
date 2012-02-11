#include "object.h"
#include "logger.h"
#include "material.h"

Object::Object(Material* material) :
  material(material)
{

}

Object::~Object()
{
  // materials are shared
  //delete material;
}

Material* Object::getMaterial() {
  return material;
}

