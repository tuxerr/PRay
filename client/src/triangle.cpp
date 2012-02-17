#include "triangle.hpp"
#include "logger.hpp"


Triangle::Triangle(VEC3F &a, VEC3F &b, VEC3F &c,
		   VEC3F &na, VEC3F &nb, VEC3F &nc,
                   VEC3F &normal,
		   Material *material) :
  Object(material), 
  a(a), 
  b(b), 
  c(c), 
  normal(normal),
  na(na.normalize()), 
  nb(nb.normalize()), 
  nc(nc.normalize())
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

VEC3F Triangle::getNA() {
  return na;
}

VEC3F Triangle::getNB() {
  return nb;
}

VEC3F Triangle::getNC() {
  return nc;
}


VEC3F Triangle::getNormal() {
    return normal;
}


VEC3F Triangle::getNormal(float u, float v) {
  // We determine the two extremities of the segment
  VEC3F uPoint = a*(1-u) + b*u;
  VEC3F vPoint = a*(1-v) + c*v;

  VEC3F point = a*(1 - u - v) + b*u + c*v;

  VEC3F uNormal = (na*((uPoint-a).norm()) + nb*((uPoint-b).norm())).normalize();
  VEC3F vNormal = (na*((uPoint-a).norm()) + nc*((uPoint-c).norm())).normalize();

  return (uNormal*((point-uPoint).norm()) + vNormal*((point-vPoint).norm())).normalize();

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
    //    *normal = this->normal;
    *normal = getNormal(u,v);
    *material = this->material;
}
