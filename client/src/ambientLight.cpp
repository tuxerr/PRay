#include "ambientLight.h"

AmbientLight::AmbientLight (float intensity, float color) :
  intensity(intensity), r(color), g(color), b(color)
{

}

AmbientLight::AmbientLight (float intensity, float r, float g, float b) :
  intensity(intensity), r(r), g(g), b(b)
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
