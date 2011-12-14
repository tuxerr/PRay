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
  int xResolution;
  int yResolution;

 public :
  Camera(const Vec4<float> &point, 
	 const Vec4<float> &direction, 
	 const Vec4<float> &normal, 
	 float viewplaneWidth,
	 float viewplaneHeight,
	 float viewplaneDist,
	 int xResolution,
	 int yResolution);
  Vec4<float> getPoint();
  Vec4<float> getDirection();
  Vec4<float> getNormal();
  float getViewplaneWidth();
  float getViewplaneHeight();
  float getViewplaneDist();
  int getXResolution();
  int getYResolution();
};

#endif
