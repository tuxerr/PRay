#ifndef DEF_RAY
#define DEF_RAY

#include "vec4.h"

class Ray {
 private :
  Vec4<float> origin;
  Vec4<float> direction;
  // Certainly needs a color but I’m not sure to know how to handle it.
 public :
  Ray(Vec4<float> origin, Vec4<float> direction);
  Vec4<float> getOrigin();
  Vec4<float> getDirection();
};

#endif
