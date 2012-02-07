#ifndef DEF_DIRECTIONALLIGHT
#define DEF_DIRECTIONALLIGHT


#include "vec3.h"
#include "color.h"
#include "light.h"

class DirectionalLight : public Light {
private :
    Vec3<float> direction;
public :
    DirectionalLight(const Color &color,
                     const Vec3<float> &direction);
    DirectionalLight(float color,
                     const Vec3<float> &direction);
    DirectionalLight(float r,
                     float g,
                     float b,
                     const Vec3<float> &direction);
    Vec3<float> getDirection();
};

#endif
