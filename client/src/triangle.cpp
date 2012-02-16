#include "triangle.hpp"
#include "logger.hpp"


Triangle::Triangle(Vec3<float> &a, Vec3<float> &b, Vec3<float> &c, Material *material) :
  Object(material), a(a), b(b), c(c), normal(((b - a) * (b - c)).normalize()),
  na(normal), nb(normal), nc(normal) 
{

}

Triangle::Triangle(Vec3<float> &a, Vec3<float> &b, Vec3<float> &c,
		   Vec3<float> &na, Vec3<float> &nb, Vec3<float> &nc,
		   Material *material) :
  Object(material), a(a), b(b), c(c), na(na.normalize()), nb(nb.normalize()), nc(nc.normalize()), normal(((b - a) * (b - c)).normalize())
{

}

Vec3<float> Triangle::getA() {
    return a;
}

Vec3<float> Triangle::getB() {
    return b;
}

Vec3<float> Triangle::getC() {
    return c;
}

Vec3<float> Triangle::getNA() {
  return na;
}

Vec3<float> Triangle::getNB() {
  return nb;
}

Vec3<float> Triangle::getNC() {
  return nc;
}

Vec3<float> Triangle::getNormal() {
    return normal;
}


Vec3<float> Triangle::getNormal(float u, float v) {
  // We determine the two extremities of the segment
  Vec3<float> uPoint = a*(1-u) + b*u;
  Vec3<float> vPoint = a*(1-v) + c*v;

  Vec3<float> point = a*(1 - u - v) + b*u + c*v;

  Vec3<float> uNormal = (na*((uPoint-a).norm()) + nb*((uPoint-b).norm())).normalize();
  Vec3<float> vNormal = (na*((uPoint-a).norm()) + nc*((uPoint-c).norm())).normalize();

  return (uNormal*((point-uPoint).norm()) + vNormal*((point-vPoint).norm())).normalize();

}

// Fast, minimum storage ray/triangle intersection
// Tomas Möller & Ben Trumbore

#define EPSILON 0.000001
#define CROSS(dest,v1,v2)                       \
    dest.x = v1.y * v2.z - v1.z * v2.y;         \
    dest.y = v1.z * v2.x - v1.x * v2.z;         \
    dest.z = v1.x * v2.y - v1.y * v2.x;
#define DOT(v1,v2) (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)
#define SUB(dest,v1,v2)                         \
    dest.x = v1.x - v2.x;                       \
    dest.y = v1.y - v2.y;                       \
    dest.z = v1.z - v2.z;

void Triangle::getIntersection(Ray &ray, float *distance, Vec3<float> *normal,
                               Material **material) {
    
    // ray : R(t) = orig + t * dir

    // point(u,v) = (1 - u - v) * A + u * B + v * C
    // (u,v) barycentric coordinates
    
    Vec3<float> edge1, edge2, tvec, pvec, qvec;
    float det, u, v; /* inv_det, t */
    
    // find vectors for two edges sharing A
    SUB(edge1, b, a);
    SUB(edge2, c, a);
    
    // begin calculating determiant - also used to calculate U parameter
    CROSS(pvec, ray.getDirection(), edge2);

    // if determinant is near zero, ray lies in plane of triangle
    det = DOT(edge1, pvec);

    if (det < EPSILON) {
        *distance = -1;
        return;
    }

    // calculate distance from A to ray origin
    SUB(tvec, ray.getOrigin(), a);

    // calculate U parameter and test bounds
    u = DOT(tvec, pvec);
    if (u < 0.0 || u > det) {
        *distance = -1;
        return;
    }

    // prepare to test V parameter
    CROSS(qvec, tvec, edge1);

    // calculate V parameter and test bounds
    v = DOT(ray.getDirection(), qvec);
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
    *distance = DOT(edge2, qvec) / det;


    /* *distance = t;*/
    //    *normal = this->normal;
    *normal = getNormal(u,v);
    *material = this->material;
}
