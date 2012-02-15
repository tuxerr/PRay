#include "logger.hpp"
#include "camera.hpp"

Camera::Camera(Vec3f point,
               Vec3f direction,
               Vec3f normal,
               float viewplaneWidth,
               float viewplaneDist,
               int xResolution,
               int yResolution,
float transFactor,
float rotatAngle,
               cameraMode mode) :
    point(point),
    direction(direction.normalize()),
    normal(normal.normalize()),
    lateral(direction.cross(normal).normalize()),
    viewplaneWidth(viewplaneWidth),
    viewplaneHeight(viewplaneWidth * yResolution / xResolution),
    viewplaneDist(viewplaneDist),
    xResolution(xResolution),
    yResolution(yResolution),
    transFactor(transFactor),
    rotatAngle(rotatAngle),
    mode(mode)
{
    if (! (direction.scalar(normal) < 1e-6)) {
        Logger::log(LOG_WARNING)<<"Incorrect camera : direction and normal are not orthogonal"<<std::endl;
    }
}

Vec3f Camera::getPoint() const {
    return point;
}

Vec3f Camera::getDirection() const {
    return direction;
}

Vec3f Camera::getNormal() const {
    return normal;
}

void Camera::setPoint(Vec3f point_) {
    point = point_;
}

void Camera::setDirection(Vec3f direction_) {
    direction = direction_.normalize();
}

void Camera::setNormal(Vec3f normal_) {
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

Vec3f Camera::getDirection(int x, int y) {
    return (direction*viewplaneDist
            + normal*(viewplaneHeight/2 - y*(viewplaneHeight/yResolution))
            + direction*normal*(viewplaneWidth/2 - x*(viewplaneWidth/xResolution))).normalize();
}

Vec3f Camera::horizontalProj(Vec3f vec) {
    float coord[4];
    vec.getCoord(coord);
    Vec3f res = Vec3f(coord[0], coord[1], 0);
    return res.normalize();
}

void Camera::translateForward() {
    switch (mode) {
    case CAMERA:
        point += direction * transFactor;
        break;
    case SCENE:
        point += horizontalProj(direction) * transFactor;
        break;
    }
}

void Camera::translateBackwards() {
    switch (mode) {
    case CAMERA:
        point -= direction * transFactor;
        break;
    case SCENE:
        point -= horizontalProj(direction) * transFactor;
        break;
    }
}

void Camera::translateLeft() {
    switch (mode) {
    case CAMERA:
        point += lateral * transFactor;
        break;
    case SCENE:
        point += horizontalProj(lateral) * transFactor;
        break;
    }
}

void Camera::translateRight() {
    switch (mode) {
    case CAMERA:
        point -= lateral * transFactor;
        break;
    case SCENE:
        point -= horizontalProj(lateral) * transFactor;
        break;
    }
}

void Camera::translateUp() {
    switch (mode) {
    case CAMERA:
        point += normal * transFactor;
        break;
    case SCENE:
        point += Vec3f(0, 0, transFactor);
        break;
    }
}

void Camera::translateDown() {
    switch (mode) {
    case CAMERA:
        point -= normal * transFactor;
        break;
    case SCENE:
        point -= Vec3f(0, 0, transFactor);
        break;
    }
}

// angle : in degrees
void Camera::rotate(float angle, Vec3f axis) {
    direction = direction.rotate(angle, axis);
    normal = normal.rotate(angle, axis);
    lateral = lateral.rotate(angle, axis);
}

void Camera::rollLeft() {
    switch (mode) {
    case CAMERA:
        rotate(rotatAngle, direction);
        break;
    case SCENE:
        rotate(rotatAngle, horizontalProj(direction));
        break;
    }
}

void Camera::rollRight() {
    switch (mode) {
    case CAMERA:
        rotate(-rotatAngle, direction);
        break;
    case SCENE:
        rotate(-rotatAngle, horizontalProj(direction));
        break;
    }
}

void Camera::pitchUp() {
    switch (mode) {
    case CAMERA:
        rotate(rotatAngle, lateral);
        break;
    case SCENE:
        rotate(rotatAngle, horizontalProj(lateral));
        break;
    }
}

void Camera::pitchDown() {
    switch (mode) {
    case CAMERA:
        rotate(-rotatAngle, lateral);
        break;
    case SCENE:
        rotate(-rotatAngle, horizontalProj(lateral));
        break;
    }
}

void Camera::yawLeft() {
    switch (mode) {
    case CAMERA:
        rotate(-rotatAngle, normal);
        break;
    case SCENE:
        rotate(-rotatAngle, Vec3f(0,0,1));
        break;
    }
}

void Camera::yawRight() {
    switch (mode) {
    case CAMERA:
        rotate(rotatAngle, normal);
        break;
    case SCENE:
        rotate(rotatAngle, Vec3f(0,0,1));
        break;
    }
}

void Camera::switchMode() {
    switch (mode) {
    case CAMERA:
        mode = SCENE;
        break;
    case SCENE:
        mode = CAMERA;
        break;
    }
}
/*
void Camera::logInformations() {
Logger::log(LOG_INFO)<<"Camera : position = ("<<point.x<<", "<<point.y<<", "<<point.z<<")"<<std::endl;
Logger::log(LOG_INFO)<<" : direction = ("<<direction.x<<", "<<direction.y<<", "<<direction.z<<")"<<std::endl;
Logger::log(LOG_INFO)<<" : normal = ("<<normal.x<<", "<<normal.y<<", "<<normal.z<<")"<<std::endl;
Logger::log(LOG_INFO)<<" : lateral = ("<<lateral.x<<", "<<lateral.y<<", "<<lateral.z<<")"<<std::endl;
}
*/
