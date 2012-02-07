#include "directionalLight.h"

DirectionalLight::DirectionalLight(const Color &color, const Vec3<float> &direction) :
  Light(color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float color, const Vec3<float> &direction) :
  Light(color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float r, float g, float b, const Vec3<float> &direction) :
  Light(r, g, b), direction(direction)
{

}

Vec3<float> DirectionalLight::getDirection() {
  return direction;
}
