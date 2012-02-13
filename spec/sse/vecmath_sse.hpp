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
#ifndef SANDBOX_VECMATH_SSE_H
#define SANDBOX_VECMATH_SSE_H

// Include SSE intrinsics
#include <xmmintrin.h>

#ifdef __SSE2__
#include <emmintrin.h>
#endif

#ifdef __SSE3__
// SSE3 includes the haddps (horizontal add) instruction
#include <pmmintrin.h>
#endif

#ifdef __SSE4_1__
// SSE4.1 includes the dpps (dot product) instruction
#include <smmintrin.h>
#endif

namespace vecmath {

// Vector template
template <>
struct Vector<float> {
    union {
        struct { float x, y, z, w; };
        __m128 v;
    };

    Vector();
    Vector(float x_, float y_, float z_);
    explicit Vector(__m128 v_);
    Vector(const Vector<float>& vector);

    Vector<float>& operator=(const Vector<float>& vector);

    float& operator[](int index);
    float operator[](int index) const;

    float length() const;
    float length_squared() const;
    Vector<float> normalize() const;

private:
    // Constructor used by Matrix
    Vector(float x_, float y_, float z_, float w_);

    friend class Matrix<float>;
};

// Point template
template <>
struct Point<float> {
    union {
        struct { float x, y, z, w; };
        __m128 v;
    };

    Point();
    Point(float x_, float y_, float z_);
    explicit Point(__m128 v_);
    Point(const Point<float>& point);

    Point<float>& operator=(const Point<float>& point);

    float& operator[](int index);
    float operator[](int index) const;

    float distance(const Point<float>& p) const;
    float distance_squared(const Point<float>& p) const;
};

// Matrix template
template <>
class Matrix<float> {
public:
    Matrix(const Matrix<float>& m);

    Matrix<float>& operator=(const Matrix<float>& m);

    static Matrix<float> identity();

    static Matrix<float> translate(const Vector<float>& v);

    static Matrix<float> rotate_x(float angle);
    static Matrix<float> rotate_y(float angle);
    static Matrix<float> rotate_z(float angle);
    static Matrix<float> rotate(const Vector<float>& axis, float angle);

    static Matrix<float> scale(float f);
    static Matrix<float> scale(float fx, float fy, float fz);

    Matrix<float> operator*(const Matrix<float>& m) const;

    Vector<float> transform(const Vector<float>& v) const;
    Point<float> transform(const Point<float>& p) const;
    Ray<float> transform(const Ray<float>& r) const;

private:
    Matrix(const Vector<float>& r0_, const Vector<float>& r1_, const Vector<float>& r2_);

    Vector<float> r0, r1, r2;
};

} // namespace vecmath

#define SANDBOX_VECMATH_SSE_IMPL_INCLUDE
#include "vecmath_sse_impl.hpp"
#undef SANDBOX_VECMATH_SSE_IMPL_INCLUDE

#endif // SANDBOX_VECMATH_SSE_H
