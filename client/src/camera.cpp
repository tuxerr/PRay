#include "camera.h"

/**
 * direction and normal vectors should be given 
 * normalized to the constructor
 */
Camera::Camera(const Vec4<float> &point, 
	       const Vec4<float> &direction, 
	       const Vec4<float> &normal,
	       float viewplaneWidth, 
	       float viewplaneHeight, 
	       float viewplaneDist,
	       int xResolution,
	       int yResolution) :
  point(point), 
  direction(direction), 
  normal(normal),
  viewplaneWidth(viewplaneWidth), 
  viewplaneHeight(viewplaneHeight), 
  viewplaneDist(viewplaneDist),
  xResolution(xResolution),
  yResolution(yResolution)
{

}

Vec4<float> Camera::getPoint() const {
  return point;
}

Vec4<float> Camera::getDirection() const {
  return direction;
}

Vec4<float> Camera::getNormal() const {
  return normal;
}

float Camera::getViewplaneWidth() const {
  return viewplaneWidth;
}

float Camera::getViewplaneHeight() const {
  return viewplaneHeight;
}

float Camera::getViewplaneDist() const {
  return viewplaneDist;
}

Vec4<float> Camera::getDirection(int x, int y) {
    return direction*viewplaneDist + 
        normal*(x*(viewplaneHeight/xResolution) - viewplaneHeight/2) + 
        direction*normal*(y*(viewplaneWidth/yResolution) - viewplaneWidth/2);
}
