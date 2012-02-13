#include "light.hpp"


Light::Light(const Color &color) :
  color(color)
{

}

Light::Light (float grey) :
  color(grey)
{

}

Light::Light (float r, float g, float b) :
  color(r, g, b)
{

}

Color Light::getColor() {
  return color;
}
