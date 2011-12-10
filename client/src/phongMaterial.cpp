#include "material.h"

Material::Material(float specularReflection, float diffuseReflection, float ambiantReflection, float shininess) : 
  specularReflection(specularReflection), diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), shininess(shininess)
{

}

float Material::getSpecularReflection() {
  return specularReflection;
}

float Material::getDiffuseReflection() {
  return diffuseReflection;
}

float Material::getAmbiantReflection() {
  return ambiantReflection;
}

float Material::getShininess() {
  return shininess;
}
