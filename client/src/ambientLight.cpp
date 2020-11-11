#include "ambientLight.hpp"

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

VEC3F AmbientLight::getDirection(__attribute__((unused)) VEC3F &point) {
    return VEC3F(0,0,0);
}
