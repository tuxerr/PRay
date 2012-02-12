/*
 * Copyright 2011 Jesper de Jong
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SANDBOX_VECMATH_SSE_IMPL_H
#define SANDBOX_VECMATH_SSE_IMPL_H

#ifndef SANDBOX_VECMATH_SSE_IMPL_INCLUDE
#error "Do not include vecmath_sse_impl.hpp directly; include vecmath_sse.hpp instead."
#endif

#include <cassert>
#include <cmath>

namespace vecmath {

// Compute dot product and return it in all four components of an XMM register
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

// Compute dot product
inline float sse_dot1_ps(__m128 a, __m128 b) {
    return _mm_cvtss_f32(sse_dot4_ps(a, b));
}

inline Vector<float>::Vector() { }

inline Vector<float>::Vector(float x_, float y_, float z_) : v(_mm_setr_ps(x_, y_, z_, 0.0f)) { }

inline Vector<float>::Vector(float x_, float y_, float z_, float w_) : v(_mm_setr_ps(x_, y_, z_, w_)) { }

inline Vector<float>::Vector(__m128 v_) : v(v_) { }

inline Vector<float>::Vector(const Vector<float>& vector) : v(vector.v) { }

inline Vector<float>& Vector<float>::operator=(const Vector<float>& vector) {
    v = vector.v;
    return *this;
}

inline float& Vector<float>::operator[](int index) {
    assert(index >= 0 && index <= 3);
    return (&x)[index];
}

inline float Vector<float>::operator[](int index) const {
    assert(index >= 0 && index <= 3);
    return (&x)[index];
}

inline float Vector<float>::length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(sse_dot4_ps(v, v)));
}

inline float Vector<float>::length_squared() const {
    return sse_dot1_ps(v, v);
}

inline Vector<float> Vector<float>::normalize() const {
    return Vector<float>(_mm_div_ps(v, _mm_sqrt_ps(sse_dot4_ps(v, v))));
}

inline Vector<float> operator+(const Vector<float>& v1, const Vector<float>& v2) {
    return Vector<float>(_mm_add_ps(v1.v, v2.v));
}

inline Vector<float>& operator+=(Vector<float>& v1, const Vector<float>& v2) {
    v1.v = _mm_add_ps(v1.v, v2.v);
    return v1;
}

inline Vector<float> operator-(const Vector<float>& v1, const Vector<float>& v2) {
    return Vector<float>(_mm_sub_ps(v1.v, v2.v));
}

inline Vector<float>& operator-=(Vector<float>& v1, const Vector<float>& v2) {
    v1.v = _mm_sub_ps(v1.v, v2.v);
    return v1;
}

inline Vector<float> operator-(const Vector<float>& v) {
    return Vector<float>(_mm_sub_ps(_mm_setzero_ps(), v.v));
}

inline Vector<float> operator*(const Vector<float>& v, float f) {
    return Vector<float>(_mm_mul_ps(v.v, _mm_set1_ps(f)));
}

inline Vector<float> operator*(float f, const Vector<float>& v) {
    return v * f;
}

inline Vector<float>& operator*=(Vector<float>& v, float f) {
    v.v = _mm_mul_ps(v.v, _mm_set1_ps(f));
    return v;
}

inline Vector<float> operator/(const Vector<float>& v, float f) {
    return Vector<float>(_mm_div_ps(v.v, _mm_set1_ps(f)));
}

inline Vector<float>& operator/=(Vector<float>& v, float f) {
    v.v = _mm_div_ps(v.v, _mm_set1_ps(f));
    return v;
}

inline float dot(const Vector<float>& v1, const Vector<float>& v2) {
    return sse_dot1_ps(v1.v, v2.v);
}

inline Vector<float> cross(const Vector<float>& v1, const Vector<float>& v2) {
    __m128 t1 = _mm_shuffle_ps(v1.v, v1.v, 0xc9);
    __m128 t2 = _mm_shuffle_ps(v1.v, v1.v, 0xd2);
    __m128 t3 = _mm_shuffle_ps(v2.v, v2.v, 0xd2);
    __m128 t4 = _mm_shuffle_ps(v2.v, v2.v, 0xc9);
    __m128 t5 = _mm_mul_ps(t1, t3);
    __m128 t6 = _mm_mul_ps(t2, t4);
    return Vector<float>(_mm_sub_ps(t5, t6));
}

inline Point<float>::Point() { }

inline Point<float>::Point(float x_, float y_, float z_) : v(_mm_setr_ps(x_, y_, z_, 1.0f)) { }

inline Point<float>::Point(__m128 v_) : v(v_) { }

inline Point<float>::Point(const Point<float>& point) : v(point.v) { }

inline Point<float>& Point<float>::operator=(const Point<float>& point) {
    v = point.v;
    return *this;
}

inline float& Point<float>::operator[](int index) {
    assert(index >= 0 && index <= 3);
    return (&x)[index];
}

inline float Point<float>::operator[](int index) const {
    assert(index >= 0 && index <= 3);
    return (&x)[index];
}

inline float Point<float>::distance(const Point<float>& p) const {
    return (*this - p).length();
}

inline float Point<float>::distance_squared(const Point<float>& p) const {
    return (*this - p).length_squared();
}

inline Point<float> operator+(const Point<float>& p, const Vector<float>& v) {
    return Point<float>(_mm_add_ps(p.v, v.v));
}

inline Point<float>& operator+=(Point<float>& p, const Vector<float>& v) {
    p.v = _mm_add_ps(p.v, v.v);
    return p;
}

inline Point<float> operator-(const Point<float>& p, const Vector<float>& v) {
    return Point<float>(_mm_sub_ps(p.v, v.v));
}

inline Point<float>& operator-=(Point<float>& p, const Vector<float>& v) {
    p.v = _mm_sub_ps(p.v, v.v);
    return p;
}

inline Vector<float> operator-(const Point<float>& p1, const Point<float>& p2) {
    return Vector<float>(_mm_sub_ps(p1.v, p2.v));
}

inline Matrix<float>::Matrix(const Matrix<float>& m) : r0(m.r0), r1(m.r1), r2(m.r2) { }

inline Matrix<float>& Matrix<float>::operator=(const Matrix<float>& m) {
    r0 = m.r0;
    r1 = m.r1;
    r2 = m.r2;
    return *this;
}

inline Matrix<float> Matrix<float>::identity() {
    return Matrix<float>(
        Vector<float>(1.0f, 0.0f, 0.0f, 0.0f),
        Vector<float>(0.0f, 1.0f, 0.0f, 0.0f),
        Vector<float>(0.0f, 0.0f, 1.0f, 0.0f));
}

inline Matrix<float> Matrix<float>::translate(const Vector<float>& v) {
    return Matrix<float>(
        Vector<float>(1.0f, 0.0f, 0.0f, v.x),
        Vector<float>(0.0f, 1.0f, 0.0f, v.y),
        Vector<float>(0.0f, 0.0f, 1.0f, v.z));
}

inline Matrix<float> Matrix<float>::rotate_x(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix<float>(
        Vector<float>(1.0f, 0.0f, 0.0f, 0.0f),
        Vector<float>(0.0f,    c,   -s, 0.0f),
        Vector<float>(0.0f,    s,    c, 0.0f));
}

inline Matrix<float> Matrix<float>::rotate_y(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix<float>(
        Vector<float>(   c, 0.0f,    s, 0.0f),
        Vector<float>(0.0f, 1.0f, 0.0f, 0.0f),
        Vector<float>(  -s, 0.0f,    c, 0.0f));
}

inline Matrix<float> Matrix<float>::rotate_z(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix<float>(
        Vector<float>(   c,   -s, 0.0f, 0.0f),
        Vector<float>(   s,    c, 0.0f, 0.0f),
        Vector<float>(0.0f, 0.0f, 1.0f, 0.0f));
}

inline Matrix<float> Matrix<float>::rotate(const Vector<float>& axis, float angle) {
    Vector<float> a = axis.normalize();

    float c = std::cos(angle);
    float s = std::sin(angle);
    float cc = 1.0f - c;

    float t1 = a.x * a.y * cc;
    float t2 = a.x * a.z * cc;
    float t3 = a.y * a.z * cc;

    float u1 = a.x * s;
    float u2 = a.y * s;
    float u3 = a.z * s;

    return Matrix<float>(
        Vector<float>(a.x * a.x * cc + c, t1 - u3, t2 + u2, 0.0f),
        Vector<float>(t1 + u3, a.y * a.y * cc + c, t3 - u1, 0.0f),
        Vector<float>(t2 - u2, t3 + u1, a.z * a.z * cc + c, 0.0f));
}

inline Matrix<float> Matrix<float>::scale(float f) {
    return Matrix<float>(
        Vector<float>(  f, 0.0f, 0.0f, 0.0f),
        Vector<float>(0.0f,   f, 0.0f, 0.0f),
        Vector<float>(0.0f, 0.0f,   f, 0.0f));
}

inline Matrix<float> Matrix<float>::scale(float fx, float fy, float fz) {
    return Matrix<float>(
        Vector<float>( fx, 0.0f, 0.0f, 0.0f),
        Vector<float>(0.0f,  fy, 0.0f, 0.0f),
        Vector<float>(0.0f, 0.0f,  fz, 0.0f));
}

inline Matrix<float> Matrix<float>::operator*(const Matrix<float>& m) const {
    __m128 r3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);

    __m128 t0 = _mm_unpacklo_ps(m.r0.v, m.r1.v);
    __m128 t1 = _mm_unpacklo_ps(m.r2.v, r3);
    __m128 t2 = _mm_unpackhi_ps(m.r0.v, m.r1.v);
    __m128 t3 = _mm_unpackhi_ps(m.r2.v, r3);

    __m128 tr0 = _mm_movelh_ps(t0, t1);
    __m128 tr1 = _mm_movehl_ps(t1, t0);
    __m128 tr2 = _mm_movelh_ps(t2, t3);
    __m128 tr3 = _mm_movehl_ps(t3, t2);

    return Matrix<float>(
        Vector<float>(sse_dot1_ps(r0.v, tr0), sse_dot1_ps(r0.v, tr1), sse_dot1_ps(r0.v, tr2), sse_dot1_ps(r0.v, tr3)),
        Vector<float>(sse_dot1_ps(r1.v, tr0), sse_dot1_ps(r1.v, tr1), sse_dot1_ps(r1.v, tr2), sse_dot1_ps(r1.v, tr3)),
        Vector<float>(sse_dot1_ps(r2.v, tr0), sse_dot1_ps(r2.v, tr1), sse_dot1_ps(r2.v, tr2), sse_dot1_ps(r2.v, tr3)));
}

inline Vector<float> Matrix<float>::transform(const Vector<float>& v) const {
    return Vector<float>(sse_dot1_ps(r0.v, v.v), sse_dot1_ps(r1.v, v.v), sse_dot1_ps(r2.v, v.v));
}

inline Point<float> Matrix<float>::transform(const Point<float>& p) const {
    return Point<float>(sse_dot1_ps(r0.v, p.v), sse_dot1_ps(r1.v, p.v), sse_dot1_ps(r2.v, p.v));
}

inline Ray<float> Matrix<float>::transform(const Ray<float>& r) const {
    return Ray<float>(transform(r.origin), transform(r.direction));
}

inline Matrix<float>::Matrix(const Vector<float>& r0_, const Vector<float>& r1_, const Vector<float>& r2_) : r0(r0_), r1(r1_), r2(r2_) { }

} // namespace vecmath

#endif // SANDBOX_VECMATH_SSE_IMPL_H
