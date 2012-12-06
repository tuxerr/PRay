#ifndef DEF_RAY
#define DEF_RAY

#include "vec3.hpp"
#include "color.hpp"

class Ray {
    friend class AABB;
    friend class PhongMaterial;
    friend class Plane;
    friend class Sphere;
    friend class Triangle;
    friend class UglyMaterial;
private:
    Color color;
    VEC3F origin;
    VEC3F direction;
public:
    int reflections;
    Ray(const VEC3F &origin, const VEC3F &direction, Color &color, int reflections = 0);
    Color getColor() const;
};

#endif
