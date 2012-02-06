#include "color.h"

Color::Color(float grey) :
  r(grey), g(grey), b(grey)
{
  
}

Color::Color(float r, float g, float b) :
  r(r), g(g), b(b)
{
  
}

float Color::getR() {
  return r;
}

float Color::getG() {
  return g;
}

float Color::getB() {
  return b;
}
