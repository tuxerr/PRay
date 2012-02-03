#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "vec3.h"

#define DEFAULT_CAM_TRANS_FACTOR  5
#define DEFAULT_CAM_ROT_ANGLE     2

typedef enum { SCENE, CAMERA } cameraMode; 

class Camera {
private :
    Vec3<float> point;
    Vec3<float> direction;
    Vec3<float> normal;
    Vec3<float> lateral;
    float viewplaneWidth;
    float viewplaneHeight;
    float viewplaneDist;
    int xResolution;
    int yResolution;
    int transFactor;
    int rotatAngle;
    cameraMode mode;
    Vec3<float> horizontalProj(Vec3<float> vec);
    void rotate(float angle, vec3<float> axis);

public :
    Camera(Vec3<float> point,
           Vec3<float> direction,
           Vec3<float> normal,
           float viewplaneWidth,
           float viewplaneHeight,
           float viewplaneDist,
           int xResolution,
           int yResolution,
	   int transFactor = DEFAULT_CAM_TRANS_FACTOR,
	   int rotatAngle = DEFAULT_CAM_ROT_ANGLE,
	   cameraMode mode = CAMERA);
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
    void translateForward();
    void translatebackwards();
    void translateLeft();
    void translateRight();
    void translateVerticalUp();
    void translateVerticalDown();
    void rollLeft();
    void rollRight();
    void pitchUp();
    void pitchDown();
    void yawLeft();
    void yawRight();
};

#endif
