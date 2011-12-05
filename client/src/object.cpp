#include "object.h"

Material Object::Object(Material material) :
  material(material)
{

}

Material Object::getMaterial() {
  return material;
}
