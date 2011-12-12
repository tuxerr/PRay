#ifndef DEF_INTERSECTION
#define DEF_INTERSECTION

#include "vec4.h"
#include "ray.h"
#include "color.h"
#include "object.h"



class Intersection {
private :
  Vec4<float> point;
  Vec4<float> normal;
  float distance;
  Object* object;
  Ray ray;
public :
  Intersection(Vec4<float> point, Vec4<float> normal, float distance, Object* object, Ray ray);
  Vec4<float> getPoint();
  Vec4<float> getNormal();
  float getDistance();
  Object getObject();
  Ray getRay();
  Color getViewedColor();
};

#endif
