#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "vec3.h"

class Camera {
private :
    Vec3<float> point;
    Vec3<float> direction;
    Vec3<float> normal;
    float viewplaneWidth;
    float viewplaneHeight;
    float viewplaneDist;
    int xResolution;
    int yResolution;

public :
    Camera(Vec3<float> point,
           Vec3<float> direction,
           Vec3<float> normal,
           float viewplaneWidth,
           float viewplaneHeight,
           float viewplaneDist,
           int xResolution,
           int yResolution);
    Vec3<float> getPoint() const;
    Vec3<float> getDirection() const;
    Vec3<float> getNormal() const;
    void setPoint(Vec3<float> point);
    void setDirection(Vec3<float> direction);
    void setNormal(Vec3<float> normal);
    float getViewplaneWidth() const;
    float getViewplaneHeight() const;
    float getViewplaneDist() const;
    int getXResolution() const;
    int getYResolution() const;
    Vec3<float> getDirection(int x, int y);
};

#endif
