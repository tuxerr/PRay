#include "triangle.hpp"

#define MIN_BOX_SIZE 0.001

Triangle::Triangle(Vertex *a, Vertex *b, Vertex *c,
                   VEC3F &normal,
		   Material *material) :
    Object(material, NULL),
    a(a), b(b), c(c),
    normal(normal)

{
    float minX, maxX, minY, maxY, minZ, maxZ;
    
    float a_[4], b_[4], c_[4];
    a->coord.getCoord(a_);
    b->coord.getCoord(b_);
    c->coord.getCoord(c_);

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

VEC3F Triangle::getNormal() {
    return normal;
}

bool Triangle::contains(Vertex *v) {
    return v == a || v == b || v == c;
}


VEC3F Triangle::getNormal(VEC3F &point) {
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
    edge1 = b->coord - a->coord;
    edge2 = c->coord - a->coord;
    
    // begin calculating determiant - also used to calculate U parameter
    pvec = ray.direction.cross(edge2);

    // if determinant is near zero, ray lies in plane of triangle
    det = edge1.scalar(pvec);

    if (det < EPSILON) {
	*distance = -1;
	return;
    }

    // calculate distance from A to ray origin
    tvec = ray.origin - a->coord;

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
