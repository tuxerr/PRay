#include "camera.h"

Camera::Camera(Vec3<float> point,
               Vec3<float> direction,
               Vec3<float> normal,
               float viewplaneWidth,
               float viewplaneHeight,
               float viewplaneDist,
               int xResolution,
               int yResolution) :
  point(point),
  direction(direction.normalize()),
  normal(normal.normalize()),
  viewplaneWidth(viewplaneWidth),
  viewplaneHeight(viewplaneHeight),
  viewplaneDist(viewplaneDist),
  xResolution(xResolution),
  yResolution(yResolution)
{

}

Vec3<float> Camera::getPoint() const {
  return point;
}

Vec3<float> Camera::getDirection() const {
  return direction;
}

Vec3<float> Camera::getNormal() const {
  return normal;
}

void Camera::setPoint(Vec3<float> point_) {
  point = point_;
}

void Camera::setDirection(Vec3<float> direction_) {
  direction = direction_.normalize();
}

void Camera::setNormal(Vec3<float> normal_) {
  normal = normal_.normalize();
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

Vec3<float> Camera::getDirection(int x, int y) {
  return (direction*viewplaneDist
         + normal*(viewplaneWidth/2 - x*(viewplaneWidth/xResolution))
	  + direction*normal*(viewplaneHeight/2 - y*(viewplaneHeight/yResolution))).normalize();
}
