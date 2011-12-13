#include "ambientLight.h"


AmbientLight::AmbientLight(float intensity, const Color &color) :
  intensity(intensity), color(color)
{

}

AmbientLight::AmbientLight (float intensity, float grey) :
  intensity(intensity), color(grey)
{

}

AmbientLight::AmbientLight (float intensity, float r, float g, float b) :
  intensity(intensity), color(r, g, b)
{

}

float AmbientLight::getIntensity() {
  return intensity;
}

Color AmbientLight::getColor() {
  return color;
}
