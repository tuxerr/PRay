#include "camera.h"

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

Vec4<float> Camera::getPoint() {
  return point;
}

Vec4<float> Camera::getDirection() {
  return direction;
}

Vec4<float> Camera::getNormal() {
  return normal;
}

float Camera::getViewplaneWidth() {
  return viewplaneWidth;
}

float Camera::getViewplaneHeight() {
  return viewplaneHeight;
}

float Camera::getViewplaneDist() {
  return viewplaneDist;
}
