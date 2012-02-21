#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "vec3.hpp"
#include <list>
#include <vector>

#define DEFAULT_CAM_TRANS_FACTOR  5
#define DEFAULT_CAM_ROT_ANGLE     1

typedef enum { SCENE, CAMERA } cameraMode; 

class Camera {
private :
    VEC3F point;
    VEC3F direction;
    VEC3F normal;
    VEC3F lateral;
    float viewplaneWidth;
    float viewplaneHeight;
    float viewplaneDist;
    int xResolution;
    int yResolution;
    float transFactor;
    float rotatAngle;
    cameraMode mode;
    VEC3F horizontalProj(VEC3F vec);
    void rotate(float angle, VEC3F axis);

public :
    Camera(VEC3F point,
           VEC3F direction,
           VEC3F normal,
           float viewplaneWidth,
           float viewplaneDist,
           int xResolution,
           int yResolution,
	   float transFactor = DEFAULT_CAM_TRANS_FACTOR,
	   float rotatAngle = DEFAULT_CAM_ROT_ANGLE,
	   cameraMode mode = CAMERA);
    VEC3F getPoint() const;
    VEC3F getDirection() const;
    VEC3F getNormal() const;
    void setPoint(VEC3F point);
    void setDirection(VEC3F direction);
    void setNormal(VEC3F normal);
    float getViewplaneWidth() const;
    float getViewplaneHeight() const;
    float getViewplaneDist() const;
    int getXResolution() const;
    int getYResolution() const;
    VEC3F getDirection(int x, int y);
    std::list<VEC3F> getDirections(int x, int y, int n);
    std::vector<VEC3F> getFourDirections(int x, int y);
    void translateForward();
    void translateBackwards();
    void translateLeft();
    void translateRight();
    void translateUp();
    void translateDown();
    void rollLeft();
    void rollRight();
    void pitchUp();
    void pitchDown();
    void yawLeft();
    void yawRight();
    void switchMode();
    //void logInformations();
};

#endif
