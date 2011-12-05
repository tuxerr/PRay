#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "vec4.h"

class Camera {
 private :
  Vec4<float> point;
  Vec4<float> direction;
  Vec4<float> normal;
  float viewplaneWidth;
  float viewplaneHeight;
  float viewplaneDist;
 public :
  Camera(Vec4<float> point, Vec4<float> direction, Vec4<float> normal, 
	 float viewplaneWidth, float viewplaneHeight, float viewplaneDist);
  Vec4<float> getPoint();
  Vec4<float> getDirection();
  Vec4<float> getNormal();
  float getViewplaneWidth();
  float getViewplaneHeight();
  float getViewplaneDist();
};

#endif
