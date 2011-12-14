#ifndef DEF_RAY
#define DEF_RAY

#include "vec4.h"
#include "color.h"

class Ray {
 private :
  Vec4<float> origin;
  Vec4<float> direction;
  Color color;
 public :
  Ray(const Vec4<float> &origin, const Vec4<float> &direction);
  Vec4<float> getOrigin() const;
  Vec4<float> getDirection() const;
  Color getColor() const;
};

#endif
