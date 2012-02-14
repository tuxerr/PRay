#ifndef DEF_Vec3_sse
#define DEF_Vec3_sse

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

template <>
class Vec3<float> {
private:
    __m128 v;

public:
    Vec3(float x=0, float y=0, float z=0);
    float norm() const;
    Vec3<float> normalize() const;
    Vec3<float> cross(Vec3<float> n);
    float scalar(Vec3<float> n) const;
    Vec3<float> operator+(Vec3<float> n);
    void operator+=(Vec3<float> n);
    Vec3<float> operator-(Vec3<float> n);
    void operator-=(Vec3<float> n);
    Vec3<float> operator*(Vec3<float> n);
    Vec3<float> operator*(float n);
    Vec3<float> operator/(float n);
    Vec3<float> rotate(float angle, Vec3<float> axis);
    Vec3<float> symmetry(Vec3<float> x);
};

/*
__m128 _mm_setr_ps(float z , float y , float x , float w );
Sets the four single-precision, floating-point values to the four inputs in reverse order.
r0 := z 
r1 := y 
r2 := x 
r3 := w 
*/
template <>
inline Vec3<float>::Vec3(float x,float y,float z) : v(_mm_setr_ps(0.0f, z ,y ,x)) {    
}

template <>
inline Vec3<float>::Vec3(__m128 v) : v(v) {    
}


inline __m128 sse_dot4_ps(__m128 a, __m128 b) {
#ifdef __SSE4_1__
    __m128 dp = _mm_dp_ps(a, b, 0xff);
#elif defined(__SSE3__)
    __m128 t1 = _mm_mul_ps(a, b);
    __m128 t2 = _mm_hadd_ps(t1, t1);
    __m128 dp = _mm_hadd_ps(t2, t2);
#else
    __m128 t1 = _mm_mul_ps(a, b);
    __m128 t2 = _mm_shuffle_ps(t1, t1, 0x93);
    __m128 t3 = _mm_add_ps(t1, t2);
    __m128 t4 = _mm_shuffle_ps(t3, t3, 0x4e);
    __m128 dp = _mm_add_ps(t3, t4);
#endif
    return dp;
}

/*
float _mm_cvtss_f32(__m128 a);
Extracts the lower order floating point value from the parameter.
r := a0
*/
/*
__m128 _mm_sqrt_ss(__m128 a ); 
Computes the square root of the lower single-precision, floating-point
value of a; the upper three single-precision, floating-point values
are passed through.
r0 := sqrt(a0)
r1 := a1 
r2 := a2
r3 := a3
*/
template <>
inline float Vec3<float>::norm() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(sse_dot4_ps(v, v)));
}

template <>
Vec3<float> Vec3<float>::normalize() const{
    return Vec3<float>(_mm_div_ps(v, _mm_sqrt_ps(sse_dot4_ps(v, v))));
}

template <>
Vec3<float> Vec3<float>::operator+(Vec3<float> n) {
    return  _mm_add_ps(n.v, v);
    n.x+=x;
    n.y+=y;
    n.z+=z;
    return n;
}

template <>
void Vec3<float>::operator+=(Vec3<float> n) {
    x+=n.x;
    y+=n.y;
    z+=n.z;
}

template <>
Vec3<float> Vec3<float>::operator-(Vec3<float> n) {
    Vec3<float> res;
    res.x=x-n.x;
    res.y=y-n.y;
    res.z=z-n.z;
    return res;
}

template <>
void Vec3<float>::operator-=(Vec3<float> n) {
    x-=n.x;
    y-=n.y;
    z-=n.z;
}

// vectorial product
template <>
Vec3<float> Vec3<float>::operator*(Vec3<float> n) {
    return cross(n);
}

template <>
Vec3<float> Vec3<float>::operator*(float n) {
    Vec3<float> res;
    res.x=x*n;
    res.y=y*n;
    res.z=z*n;
    return res;
}

template <>
Vec3<float> Vec3<float>::operator/(float n) {
    Vec3<float> res;
    res.x=x/n;
    res.y=y/n;
    res.z=z/n;
    return res;
}

//cross product (vector product)
template <>
Vec3<float> Vec3<float>::cross(Vec3<float> n) {
    Vec3<float> res;
    res.x=y*n.z-z*n.y;
    res.y=z*n.x-x*n.z;
    res.z=x*n.y-y*n.x;
    return res;
}

//scalar product (dot product)
template <>
float Vec3<float>::scalar(Vec3<float> n) const {
    return n.x*x+n.y*y+n.z*z;
}

// Rodrigues' rotation formula
// phi : angle in degrees
// axis : must be of norm 1
template <>
Vec3<float> Vec3<float>::rotate(float phi, Vec3<float> axis) {
    phi = phi * 3.14159265  / 180.0; // angle in radians
    return (*this) * cos(phi)
        + axis * (*this) * sin(phi)
        + axis * axis.scalar(*this) * ((float)1.0 - cos(phi)) ;
       
}

template <>
Vec3<float> Vec3<float>::symmetry(Vec3<float> x) {
    return x*(2*(*this).scalar(x)) + (*this)*(-1);
}

#endif
