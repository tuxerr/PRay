#include "object.h"

#include "material.h"

Object::Object(const Material & material) :
  material(&material)
{

}

Material Object::getMaterial() {
  return *material;
}
