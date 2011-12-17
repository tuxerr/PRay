#include "object.h"
#include "logger.h"
#include "material.h"

Object::Object(Material* material) :
  material(material)
{

}

Object::~Object()
{
  delete material; // to improve to enable shared materials
}

Material* Object::getMaterial() {
  return material;
}

