#include "object.h"

Object::Object(const Material &material) :
  material(material)
{

}

Material Object::getMaterial() {
  return material;
}
