#include "directionalLight.h"

DirectionalLight::DirectionalLight(float intensity, Color color, Vec4<float> direction) :
  AmbientLight(intensity, color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float intensity, float color, Vec4<float> direction) :
  AmbientLight(intensity, color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float intensity, float r, float g, float b, Vec4<float> direction) :
  AmbientLight(intensity, r, g, b), direction(direction)
{

}

Vec4<float> DirectionalLight::getDirection() {
  return direction;
}
