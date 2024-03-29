#include "directionalLight.hpp"
#include "logger.hpp"


DirectionalLight::DirectionalLight(const Color &color, const VEC3F &direction) :
    Light(color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float color, const VEC3F &direction) :
    Light(color), direction(direction)
{

}

DirectionalLight::DirectionalLight(float r, float g, float b, const VEC3F &direction) :
    Light(r, g, b), direction(direction)
{

}

VEC3F DirectionalLight::getDirection() {
    return direction;
}

VEC3F DirectionalLight::getDirection(__attribute__((unused)) VEC3F &point) {
    return this->direction;
}
