#include "object.hpp"
#include "logger.hpp"
#include "material.hpp"

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

