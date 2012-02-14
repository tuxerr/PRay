#include "vec3f_sse.hpp"

/*
__m128 _mm_setr_ps(float z , float y , float x , float w );
Sets the four single-precision, floating-point values to the four inputs in reverse order.
r0 := z 
r1 := y 
r2 := x 
r3 := w 
*/
inline Vec3f::Vec3f(float x,float y,float z) : v(_mm_setr_ps(0.0f, z ,y ,x)) {    
}

inline Vec3f::Vec3f(__m128 v) : v(v) {    
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
inline float Vec3f::norm() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(sse_dot4_ps(v, v)));
}

/*
__m128 _mm_div_ps(__m128 a, __m128 b );
Divides the four single-precision, floating-point values of a and b.
r0 := a0 / b0
r1 := a1 / b1
r2 := a2 / b2
r3 := a3 / b3
*/
/*
__m128 _mm_sqrt_ps(__m128 a );
Computes the square roots of the four single-precision, floating-point
values of a.
r0 := sqrt(a0)
r1 := sqrt(a1)
r2 := sqrt(a2)
r3 := sqrt(a3)
*/
inline Vec3f Vec3f::normalize() const{
    return Vec3f(_mm_div_ps(v, _mm_sqrt_ps(sse_dot4_ps(v, v))));
}

/*
__m128 _mm_add_ps(__m128 a , __m128 b );
Adds the four single-precision, floating-point values of a and b
r0 := a0 + b0
r1 := a1 + b1
r2 := a2 + b2
r3 := a3 + b3
*/
inline Vec3f Vec3f::operator+(Vec3f& n) {
    return Vec3f(_mm_add_ps(n.v, v));
}

inline void Vec3f::operator+=(Vec3f& n) {
    v = _mm_add_ps(v, n.v);
}

inline Vec3f Vec3f::operator-(Vec3f& n) {
    return Vec3f(_mm_sub_ps(n.v, v));;
}

inline void Vec3f::operator-=(Vec3f& n) {
    v = _mm_sub_ps(v, n.v);
}

inline Vec3f Vec3f::operator*(Vec3f& n) {
    return cross(n);
}

/*
__m128 _mm_set1_ps(float w );
Sets the four single-precision, floating-point values to w.
r0 := w
r1 := w
r2 := w
r3 := w 
*/
inline Vec3f Vec3f::operator*(float f) {
    return Vec3f(_mm_mul_ps(v, _mm_set1_ps(f)));
}

inline Vec3f Vec3f::operator/(float f) {
    return Vec3f(_mm_div_ps(v, _mm_set1_ps(f)));
}

//cross product (vector product)
inline Vec3f Vec3f::cross(Vec3f& n) {
    __m128 t1 = _mm_shuffle_ps(v, v, 0xc9);
    __m128 t2 = _mm_shuffle_ps(v, v, 0xd2);
    __m128 t3 = _mm_shuffle_ps(n.v, n.v, 0xd2);
    __m128 t4 = _mm_shuffle_ps(n.v, n.v, 0xc9);
    __m128 t5 = _mm_mul_ps(t1, t3);
    __m128 t6 = _mm_mul_ps(t2, t4);
    return Vec3f(_mm_sub_ps(t5, t6));
}

//scalar product (dot product)
inline float Vec3f::scalar(Vec3f& n) const {
    return _mm_cvtss_f32(sse_dot4_ps(this->v, n.v));
}

// Rodrigues' rotation formula
// phi : angle in degrees
// axis : must be of norm 1
Vec3f Vec3f::rotate(float phi, Vec3f& axis) {
    phi = phi * 3.14159265  / 180.0; // angle in radians
    Vec3f t1 = (*this) * cos(phi);
    Vec3f t2 = axis * (*this) * sin(phi);
    Vec3f t3 = axis * axis.scalar(*this) * ((float)1.0 - cos(phi));
    return t1 + t2 + t3;
/*
    return (*this) * cos(phi)
        + axis * (*this) * sin(phi)
        + axis * axis.scalar(*this) * ((float)1.0 - cos(phi)) ;
*/   
}

Vec3f Vec3f::symmetry(Vec3f& x) {
    Vec3f t1 = x*(2*(*this).scalar(x));
    Vec3f t2 = (*this)*(-1);
    return t1 + t2;
/*
    return x*(2*(*this).scalar(x)) + (*this)*(-1);
*/
}
