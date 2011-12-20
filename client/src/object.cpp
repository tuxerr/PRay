#include "object.h"
#include "logger.h"
#include "material.h"

Object::Object(Material* material) :
  material(material)
{

}

Object::~Object()
{
  // TODO: improve to enable shared materials
  delete material;
}

Material* Object::getMaterial() {
  return material;
}

