#ifndef DEF_RAY
#define DEF_RAY

#include "vec3.hpp"
#include "color.hpp"

class Ray {
 private :
  Vec3<float> origin;
  Vec3<float> direction;
  Color color;
 public :
  Ray(const Vec3<float> &origin, const Vec3<float> &direction, Color &color, int reflections = 0);
  Vec3<float> getOrigin() const;
  Vec3<float> getDirection() const;
  Color getColor() const;
  int reflections;
};

#endif
