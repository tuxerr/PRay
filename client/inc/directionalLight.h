#ifndef DEF_DIRECTIONALLIGHT
#define DEF_DIRECTIONALLIGHT

#include "ambientLight.h"
#include "vec4.h"

class DirectionalLight : public AmbientLight {
 private :
  Vec4<float> direction;
 public :
  DirectionalLight(float intensity, float color, Vec4<float> direction);
  DirectionalLight(float intensity, float r, float g, float b, Vec4<float> direction);
  Vec4<float> getDirection();
};

#endif
