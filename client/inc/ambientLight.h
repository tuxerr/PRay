#ifndef DEF_AMBIENTLIGHT
#define DEF_AMBIENTLIGHT

#include "color.h"

class AmbientLight {
 private :
  float intensity;
  Color color;
 public :
  AmbientLight (float intensity, Color color);
  AmbientLight (float intensity, float grey);
  AmbientLight (float intensity, float r, float g, float b);
  float getIntensity();

};

#endif
