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


float determinant(VEC3F x_, VEC3F y_, VEC3F z_) {
    float x[4];
    x_.getCoord(x);
    float y[4];
    y_.getCoord(y);
    float z[4];
    z_.getCoord(z);
    
    return x[0]*y[1]*z[2] + y[0]*z[1]*x[2] + z[0]*x[1]*z[2] 
	- z[0]*y[1]*x[2] - y[0]*x[1]*z[2] - x[0]*z[1]*y[2];
}


int lineIntersection(VEC3F a, VEC3F da, VEC3F b, VEC3F db, VEC3F *res) {
    
    VEC3F dadb = da*db;

    float ndadb2 = dadb.norm();
    ndadb2 = ndadb2*ndadb2;

    if(fabs(ndadb2) > 0.0001) {
	float t = determinant((b-a),db,dadb) / ndadb2;
	*res = a + da*t;
	return 0;
    } else {
	return 1;
    }
}


VEC3F Triangle::getNormal(VEC3F &point) {

    // We determine the two extremities of the segment
    VEC3F uPoint = a + ((b-a).normalize())*((point-a).scalar((b-a).normalize()));

    VEC3F up = (point - uPoint).normalize();
    VEC3F ac = (c-a).normalize();
    VEC3F bc = (c-b).normalize();
    VEC3F uNormal = (nb*((uPoint-a).norm()) + na*((uPoint-b).norm())).normalize();
    VEC3F vNormal;
    VEC3F vPoint;
    int inter = -1;
    inter = lineIntersection(uPoint, up, a, ac, &vPoint);

    if(inter !=0) {
	inter = lineIntersection(uPoint, up, b, bc, &vPoint);
	vNormal = (nc*((vPoint-b).norm()) + nb*((vPoint-c).norm())).normalize();
    } else {
	vNormal = (nc*((vPoint-a).norm()) + na*((vPoint-c).norm())).normalize();
    }
    return (vNormal*((point-uPoint).norm()) + uNormal*((point-vPoint).norm())).normalize();
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

     if (u != u || v != v) {
	 //*normal = this->normal;
     } else {
       VEC3F point = ray.getOrigin() + (ray.getDirection())*(*distance);
       *normal = getNormal(point);
     }

    *material = this->material;
}
