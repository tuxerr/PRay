#ifndef DEF_INTERSECTION
#define DEF_INTERSECTION

#include "vec4.h"
#include "material.h"


class Intersection {
 private :
  Vec4<float> point;
  Vec4<float> normal;
  float distance;
  Material material;
 public :
  Intersection(Vec4<float> point, Vec4<float> normal, float distance, Material material);
  Vec4<float> getPoint();
  Vec4<float> getNormal();
  float getDistance();
  Material getMaterial();
};

#endif
