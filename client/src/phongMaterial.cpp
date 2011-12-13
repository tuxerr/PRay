#include "phongMaterial.h"

PhongMaterial::PhongMaterial(const Color &color, float specularReflection, float diffuseReflection, float ambiantReflection, float shininess) : 
  color(color), specularReflection(specularReflection), diffuseReflection(diffuseReflection),
  ambiantReflection(ambiantReflection), shininess(shininess)
{

}

Color PhongMaterial::getColor() {
  return color;
}

float PhongMaterial::getSpecularReflection() {
  return specularReflection;
}

float PhongMaterial::getDiffuseReflection() {
  return diffuseReflection;
}

float PhongMaterial::getAmbiantReflection() {
  return ambiantReflection;
}

float PhongMaterial::getShininess() {
  return shininess;
}

Color PhongMaterial::renderRay(const Ray &ray, const Vec4<float> &normal, Scene *scene) {
  return color; //TODO
}
