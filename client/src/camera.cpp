#include "logger.hpp"
#include "camera.hpp"
#include <cstdlib>

Camera::Camera(VEC3F point,
               VEC3F direction,
               VEC3F normal,
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
    if (! (direction.scalar(normal) < 1e-5)) {
        Logger::log(LOG_WARNING)<<"Incorrect camera : direction and normal are not orthogonal"<<std::endl;
    }
}

VEC3F Camera::getPoint() const {
    return point;
}

VEC3F Camera::getDirection() const {
    return direction;
}

VEC3F Camera::getNormal() const {
    return normal;
}

void Camera::setPoint(VEC3F point_) {
    point = point_;
}

void Camera::setDirection(VEC3F direction_) {
    direction = direction_.normalize();
}

void Camera::setNormal(VEC3F normal_) {
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

VEC3F Camera::getDirection(int x, int y) {
    return (direction*viewplaneDist
            + normal*(viewplaneHeight/2 - y*(viewplaneHeight/yResolution))
            + lateral*(viewplaneWidth/2 - x*(viewplaneWidth/xResolution))).normalize();
}

std::list<VEC3F> Camera::getDirections(int x, int y, int n) {
    std::list<VEC3F> directions;
    
    for (int i = 0 ; i < n ; i++) {
        float h = (float)y - 0.5 + (float)rand() / (float)RAND_MAX;
        float w = (float)x - 0.5 + (float)rand() / (float)RAND_MAX;

        directions.push_back((direction*viewplaneDist
                              + normal*(viewplaneHeight/2 - h*(viewplaneHeight/yResolution))
                              + lateral*(viewplaneWidth/2 - w*(viewplaneWidth/xResolution))).normalize());
    }

    return directions;
}

std::vector<VEC3F> Camera::getFourDirections(int x, int y) {
    std::vector<VEC3F> directions;
    float coordX[4];
    float coordY[4];
    
    coordX[0] = (float)x - 0.5 + 0.5 * (float)rand() / (float)RAND_MAX;
    coordY[0] = (float)y - 0.5 + 0.5 * (float)rand() / (float)RAND_MAX;

    coordX[1] = (float)x       + 0.5 * (float)rand() / (float)RAND_MAX;
    coordY[1] = (float)y - 0.5 + 0.5 * (float)rand() / (float)RAND_MAX;

    coordX[2] = (float)x - 0.5 + 0.5 * (float)rand() / (float)RAND_MAX;
    coordY[2] = (float)y       + 0.5 * (float)rand() / (float)RAND_MAX;

    coordX[3] = (float)x       + 0.5 * (float)rand() / (float)RAND_MAX;
    coordY[3] = (float)y       + 0.5 * (float)rand() / (float)RAND_MAX;

    for (int i = 0 ; i < 4 ; i++) {
        directions.push_back((direction * viewplaneDist
                              + normal * ( viewplaneHeight / 2 
                                           - coordY[i] * ( viewplaneHeight / yResolution ))
                              + lateral * ( viewplaneWidth / 2 
                                            - coordX[i] * ( viewplaneWidth / xResolution ))
                                 ).normalize());
    }

    return directions;
} 

VEC3F Camera::horizontalProj(VEC3F vec) {
    float coord[4];
    vec.getCoord(coord);
    VEC3F res = VEC3F(coord[0], coord[1], 0);
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
        point += VEC3F(0, 0, transFactor);
        break;
    }
}

void Camera::translateDown() {
    switch (mode) {
    case CAMERA:
        point -= normal * transFactor;
        break;
    case SCENE:
        point -= VEC3F(0, 0, transFactor);
        break;
    }
}

// angle : in degrees
void Camera::rotate(float angle, VEC3F axis) {
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
        rotate(-rotatAngle, VEC3F(0,0,1));
        break;
    }
}

void Camera::yawRight() {
    switch (mode) {
    case CAMERA:
        rotate(rotatAngle, normal);
        break;
    case SCENE:
        rotate(rotatAngle, VEC3F(0,0,1));
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
