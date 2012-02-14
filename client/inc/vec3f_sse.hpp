#ifndef DEF_VEC3F_SSE
#define DEF_VEC3F_SSE

#include <cmath>

// SSE intrinsics
#include <xmmintrin.h>

#ifdef __SSE2__
#include <emmintrin.h>
#endif

#ifdef __SSE3__
#include <pmmintrin.h>
#endif

#ifdef __SSE4_1__
#include <smmintrin.h>
#endif

class Vec3f {
private:
    __m128 v;
    Vec3f(__m128 v);

public:
    Vec3f(float x=0, float y=0, float z=0);
    float norm() const;
    Vec3f normalize() const;
    Vec3f cross(Vec3f& n);
    float scalar(Vec3f& n) const;
    Vec3f operator+(Vec3f& n);
    void operator+=(Vec3f& n);
    Vec3f operator-(Vec3f& n);
    void operator-=(Vec3f& n);
    Vec3f operator*(Vec3f& n);
    Vec3f operator*(float n);
    Vec3f operator/(float n);
    Vec3f rotate(float angle, Vec3f& axis);
    Vec3f symmetry(Vec3f& x);
};

#endif
