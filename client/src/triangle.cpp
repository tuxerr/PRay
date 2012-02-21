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


/*
  We want to solve the linear problem :
  
  ax - bx + dax*s - dbx*t = 0
  ay - by + day*s - dby*t = 0
  az - bz + daz*s - dbz*t = 0
  
*/

int lineIntersection(VEC3F a_, VEC3F da_, VEC3F b_, VEC3F db_, VEC3F *res) {
    float a[4];
    a_.getCoord(a);
    float b[4];
    b_.getCoord(b);
    float da[4];
    da_.getCoord(da);
    float db[4];
    db_.getCoord(db);
  
    VEC3F inter;
    float inv[4];

    float s = 0.;
    float t = 0.;

    float u = b[0]-a[0];
    float v = b[1]-a[1];
    float w = b[2]-a[2];

    float det = -da[0]*db[1] + da[1]*db[0];
    if(fabs(det) > 0.001) {
    
	inv[0] = -db[1]/det;
	inv[1] = da[1]/det;
	inv[2] = -db[0]/det;
	inv[3] = da[0]/det;
    
	s = inv[0]*u + inv[1]*v;
	t = inv[2]*u + inv[3]*v;
    
    } else if (fabs(det = -da[0]*db[2] + da[2]*db[0]) > 0.001) {

	inv[0] = -db[2]/det;
	inv[1] = da[2]/det;
	inv[2] = -db[0]/det;
	inv[3] = da[0]/det;

	s = inv[0]*u + inv[1]*w;
	t = inv[2]*u + inv[3]*w;

    } else if (fabs(det = -da[1]*db[2] + da[2]*db[1]) > 0.001) {

	inv[0] = -db[2]/det;
	inv[1] = da[2]/det;
	inv[2] = -db[1]/det;
	inv[3] = da[1]/det;

	s = inv[0]*v + inv[1]*w;
	t = inv[2]*v + inv[3]*w;

    }

    //  Logger::log(LOG_INFO)<<" res resol" << u << "    " << v << std::endl;

    if(fabs(a[0] - b[0] + da[0]*s - db[0]*t) < 0.0001
       && fabs(a[1] - b[1] + da[1]*s - db[1]*t) < 0.0001
       && fabs(a[2] - b[2] + da[2]*s - db[2]*t) < 0.0001) {   

	Logger::log(LOG_INFO)<< "RETURN" << a[0]+da[0]*s << a[1]+da[1]*s << a[2]+da[2]*s << std::endl;
    
	*res = VEC3F(b[0]+db[0]*s, b[1]+db[1]*s, b[2]+db[2]*s);
	return 0;
    } else {
	return 1;
    }
  
}


//   VEC3F Triangle::getNormal(float u, float v) {

VEC3F Triangle::getNormal(VEC3F &point) {

    // // TEST
  
    // VEC3F t1_ = VEC3F(0,0,0);
    // VEC3F dt1_ = VEC3F(0,1,0);
    // VEC3F t2_ = VEC3F(0,42,1);
    // VEC3F dt2_ = VEC3F(0,0,-1);

    // VEC3F test;
    // lineIntersection(t1_, dt1_, t2_, dt2_, &test);

    // float testco[4];
    // test.getCoord(testco);

    // Logger::log(LOG_INFO)<<"########################TEST " 
    // 		       << testco[0] << " "
    // 		       << testco[1] << " "
    // 		       << testco[2] << " "
    // 		       << std::endl;

    // /*
    //   On resoud donc le systeme :
    //   t = 1
    //   0 = 42 - v
    //   0 = 0

    // */

    // // TSET

    Logger::log(LOG_INFO)<<"######################## a " << std::endl;
    a.printLog();

    Logger::log(LOG_INFO)<<"######################## b " << std::endl;
    b.printLog();

    Logger::log(LOG_INFO)<<"######################## c " << std::endl;
    c.printLog();

    Logger::log(LOG_INFO)<<"######################## point " << std::endl;
    point.printLog();



    // We determine the two extremities of the segment
    VEC3F uPoint = a + ((b-a).normalize())*((point-a).scalar((b-a).normalize()));
  
    Logger::log(LOG_INFO)<<"######################## u " << std::endl;
    uPoint.printLog();


    VEC3F up = (point - uPoint).normalize();
    VEC3F ac = (c-a).normalize();
    VEC3F bc = (c-b).normalize();
    VEC3F uNormal = (nb*((uPoint-a).norm()) + na*((uPoint-b).norm())).normalize();
    VEC3F vNormal;
    VEC3F vPoint;
    int inter = -1;
    inter = lineIntersection(uPoint, up, a, ac, &vPoint);


    //  Logger::log(LOG_INFO)<<"av.scalar(ac) " << ((vPoint-a).normalize()).scalar((c-a).normalize()) << std::endl;

    //  Logger::log(LOG_INFO)<<"up.scalar(uv) " << ((point-uPoint).normalize()).scalar((vPoint-uPoint).normalize()) << std::endl;

    if(inter !=0) {
    
	inter = lineIntersection(uPoint, up, b, bc, &vPoint);

	vNormal = (nc*((vPoint-b).norm()) + nb*((vPoint-c).norm())).normalize();
    } else {
	vNormal = (nc*((vPoint-a).norm()) + na*((vPoint-c).norm())).normalize();
    }

    Logger::log(LOG_INFO)<<"#############------########### v " << std::endl;
    vPoint.printLog();

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

    //  if (u != u || v != v) {
    *normal = this->normal;
    //  } else {
    //    VEC3F point = ray.getOrigin() + (ray.getDirection())*(*distance);
    //    *normal = getNormal(point);
    //  }

    *material = this->material;
}
