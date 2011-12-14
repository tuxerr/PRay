#ifndef DEF_AMBIENTLIGHT
#define DEF_AMBIENTLIGHT

#include "color.h"

class AmbientLight {
private :
    float intensity;
    Color color;
public :
    AmbientLight (float intensity, const Color &color);
    AmbientLight (float intensity =1, float grey =1);
    AmbientLight (float intensity, float r, float g, float b);
    float getIntensity();
    Color getColor();
};

#endif
