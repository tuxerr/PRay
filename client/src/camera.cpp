#include "camera.h"

Camera::Camera(Vec4<float> point, Vec4<float> direction, Vec4<float> normal,
	       float viewplaneWidth, float viewplaneHeight, float viewplaneDist) :
  point(point), direction(direction), normal(normal),
  viewplaneWidth(viewplaneWidth), 
  viewplaneHeight(viewplaneHeight), 
  viewplaneDist(viewplaneDist)
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
