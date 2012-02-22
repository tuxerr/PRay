#include "pointLight.hpp"

PointLight::PointLight(const Color &color,const VEC3F &point) :
    Light(color), point(point)
{

}

PointLight::PointLight(float color, const VEC3F &point) :
    Light(color), point(point)
{

}

PointLight::PointLight(float r, float g, float b, const VEC3F &point) :
    Light(r, g, b), point(point)
{
    
}

VEC3F PointLight::getPoint() {
    return point;
}

VEC3F PointLight::getDirection(VEC3F &point) {
    return (point - this->point).normalize();
}
