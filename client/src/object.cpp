#include "object.h"

#include "material.h"

Object::Object(Material &material) :
  material(&material)
{

}

Material Object::getMaterial() {
  return *material;
}
