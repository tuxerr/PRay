#ifndef DEF_DIRECTIONALLIGHT
#define DEF_DIRECTIONALLIGHT


#include "vec4.h"
#include "color.h"
#include "ambientLight.h"

class DirectionalLight : public AmbientLight {
 private :
  Vec4<float> direction;
 public :
  DirectionalLight(float intensity, const Color &color, const Vec4<float> &direction);
  DirectionalLight(float intensity, float color, const Vec4<float> &direction);
  DirectionalLight(float intensity, float r, float g, float b, const Vec4<float> &direction);
  Vec4<float> getDirection();
};

#endif
