#include "object.h"

Object::Object(Material material) :
  material(material)
{

}

Material Object::getMaterial() {
  return material;
}
