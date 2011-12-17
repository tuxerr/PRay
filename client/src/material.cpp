#include "material.h"

// to avoid linking problem
Color Material::renderRay(const Ray &ray, const Vec4<float> &normal, Scene *scene) {
    return Color(0,255,0);
}
