#include "directionalLight.h"

DirectionalLight::DirectionalLight(float intensity, const Color &color, const Vec4<float> &direction) :
  AmbientLight(intensity, color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float intensity, float color, const Vec4<float> &direction) :
  AmbientLight(intensity, color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float intensity, float r, float g, float b, const Vec4<float> &direction) :
  AmbientLight(intensity, r, g, b), direction(direction)
{

}

Vec4<float> DirectionalLight::getDirection() {
  return direction;
}
