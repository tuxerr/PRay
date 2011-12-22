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
    Camera(Vec4<float> point,
           Vec4<float> direction,
           Vec4<float> normal,
           float viewplaneWidth,
           float viewplaneHeight,
           float viewplaneDist,
           int xResolution,
           int yResolution);
    Vec4<float> getPoint() const;
    Vec4<float> getDirection() const;
    Vec4<float> getNormal() const;
    void setPoint(Vec4<float> point_);
    float getViewplaneWidth() const;
    float getViewplaneHeight() const;
    float getViewplaneDist() const;
    int getXResolution() const;
    int getYResolution() const;
    Vec4<float> getDirection(int x, int y);
};

#endif
