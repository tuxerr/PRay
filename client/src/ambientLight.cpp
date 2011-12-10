#include "ambientLight.h"


AmbientLight::AmbientLight(float intensity, Color color) :
  intensity(intensity), color(color)
{

}

AmbientLight::AmbientLight (float intensity, float grey) :
  intensity(intensity), color(grey)
{

}

AmbientLight::AmbientLight (float intensity, float r, float g, float b) :
  intensity(intensity), Color(r, g, b)
{

}

float AmbientLight::getIntensity() {
  return intensity;
}

float AmbientLight::getR() {
  return r;
}

float AmbientLight::getG() {
  return g;
}

float AmbientLight::getB() {
  return b;
}
