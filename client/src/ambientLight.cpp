#include "ambientLight.h"

AmbientLight::AmbientLight(const Color &color) :
  Light(color)
{

}

AmbientLight::AmbientLight (float grey) :
  Light(grey)
{

}

AmbientLight::AmbientLight (float r, float g, float b) :
  Light(r, g, b)
{

}
