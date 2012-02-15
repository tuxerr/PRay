#include "triangle.hpp"
#include "logger.hpp"

Triangle::Triangle(VEC3F &a, VEC3F &b, VEC3F &c, Material *material) :
    Object(material), a(a), b(b), c(c), normal(((b - a) * (b - c)).normalize())
{

}

VEC3F Triangle::getA() {
    return a;
}

VEC3F Triangle::getB() {
    return b;
}

VEC3F Triangle::getC() {
    return c;
}

VEC3F Triangle::getNormal() {
    return normal;
}

// Fast, minimum storage ray/triangle intersection
// Tomas Möller & Ben Trumbore

#define EPSILON 0.000001

void Triangle::getIntersection(Ray &ray, float *distance, VEC3F *normal,
                               Material **material) {
    
    // ray : R(t) = orig + t * dir

    // point(u,v) = (1 - u - v) * A + u * B + v * C
    // (u,v) barycentric coordinates
    
    VEC3F edge1, edge2, tvec, pvec, qvec;
    float det, u, v; /* inv_det, t */
    
    // find vectors for two edges sharing A
    edge1 = b - a;
    edge2 = c - a;
    
    // begin calculating determiant - also used to calculate U parameter
    pvec = ray.getDirection().cross(edge2);

    // if determinant is near zero, ray lies in plane of triangle
    det = edge1.scalar(pvec);

    if (det < EPSILON) {
        *distance = -1;
        return;
    }

    // calculate distance from A to ray origin
    tvec = ray.getOrigin() - a;

    // calculate U parameter and test bounds
    u = tvec.scalar(pvec);
    if (u < 0.0 || u > det) {
        *distance = -1;
        return;
    }

    // prepare to test V parameter
    qvec = tvec.cross(edge1);

    // calculate V parameter and test bounds
    v = ray.getDirection().scalar(qvec);
    if (v < 0.0 || u + v > det) {
        *distance = -1;
        return;
    }

    // calculate t, scale parameters, ray intersects triangle
    /*t = DOT(edge2, qvec);
      inv_det = 1.0 / det;
      t *= inv_det;
      u *= inv_det;
      v *= inv_det;*/
    *distance = edge2.scalar(qvec) / det;

    /* *distance = t;*/
    *normal = this->normal;
    *material = this->material;
}
