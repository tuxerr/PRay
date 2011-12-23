#ifndef DEF_DIRECTIONALLIGHT
#define DEF_DIRECTIONALLIGHT


#include "vec3.h"
#include "color.h"
#include "ambientLight.h"

class DirectionalLight : public AmbientLight {
private :
    Vec3<float> direction;
public :
    DirectionalLight(float intensity,
                     const Color &color,
                     const Vec3<float> &direction);
    DirectionalLight(float intensity,
                     float color,
                     const Vec3<float> &direction);
    DirectionalLight(float intensity,
                     float r,
                     float g,
                     float b,
                     const Vec3<float> &direction);
    Vec3<float> getDirection();
};

#endif
