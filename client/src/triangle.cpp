#include "triangle.hpp"

#define MIN_BOX_SIZE 0.001

Triangle::Triangle(VEC3F &a, VEC3F &b, VEC3F &c,
		   VEC3F &na, VEC3F &nb, VEC3F &nc,
                   VEC3F &normal,
		   Material *material) :
    Object(material, NULL),
    a(a), 
    b(b), 
    c(c), 
    normal(normal),
    na(na.normalize()), 
    nb(nb.normalize()), 
    nc(nc.normalize())
{
    float minX, maxX, minY, maxY, minZ, maxZ;
    
    float a_[4], b_[4], c_[4];
    a.getCoord(a_);
    b.getCoord(b_);
    c.getCoord(c_);

    minX = std::min(a_[0], std::min(b_[0], c_[0]));
    maxX = std::max(a_[0], std::max(b_[0], c_[0]));
    minY = std::min(a_[1], std::min(b_[1], c_[1]));
    maxY = std::max(a_[1], std::max(b_[1], c_[1]));
    minZ = std::min(a_[2], std::min(b_[2], c_[2]));
    maxZ = std::max(a_[2], std::max(b_[2], c_[2]));

    if (maxX - minX < MIN_BOX_SIZE) {
        float meanX = (minX + maxX) / 2.0;
        minX = meanX - MIN_BOX_SIZE / 2.0;
        maxX = meanX + MIN_BOX_SIZE / 2.0;
    }

    if (maxY - minY < MIN_BOX_SIZE) {
        float meanY = (minY + maxY) / 2.0;
        minY = meanY - MIN_BOX_SIZE / 2.0;
        maxY = meanY + MIN_BOX_SIZE / 2.0;
    }

    if (maxZ - minZ < MIN_BOX_SIZE) {
        float meanZ = (minZ + maxZ) / 2.0;
        minZ = meanZ - MIN_BOX_SIZE / 2.0;
        maxZ = meanZ + MIN_BOX_SIZE / 2.0;
    }

    aabb = new AABB(minX, maxX, minY, maxY, minZ, maxZ);
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
    //    Logger::log(LOG_DEBUG) << "inter " << inter << std::endl;

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
    pvec = ray.direction.cross(edge2);

    // if determinant is near zero, ray lies in plane of triangle
    det = edge1.scalar(pvec);

    if (det < EPSILON) {
	*distance = -1;
	return;
    }

    // calculate distance from A to ray origin
    tvec = ray.origin - a;

    // calculate U parameter and test bounds
    u = tvec.scalar(pvec);
    if (u < 0.0 || u > det) {
	*distance = -1;
	return;
    }

    // prepare to test V parameter
    qvec = tvec.cross(edge1);

    // calculate V parameter and test bounds
    v = ray.direction.scalar(qvec);
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
	 *normal = this->normal;
     } else {
       VEC3F point = ray.origin + (ray.direction)*(*distance);
       *normal = getNormal(point);
     }

    *material = this->material;
}
