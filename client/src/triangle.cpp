#include "triangle.h"
#include "logger.h"

Triangle::Triangle(Vec4<float> &a, Vec4<float> &b, Vec4<float> &c, Material *material) :
  Object(material), a(a), b(b), c(c), normal(((b - a) * (b - c)).normalize())
{

}

Vec4<float> Triangle::getA() {
  return a;
}

Vec4<float> Triangle::getB() {
  return b;
}

Vec4<float> Triangle::getC() {
  return c;
}

Vec4<float> Triangle::getNormal() {
  return normal;
}

void Triangle::getIntersection(Ray &ray, float *distance, Vec4<float> *normal, 
		     Material **material) {
  float nv = (this->normal).scalar(ray.getDirection());
  /*  Logger::log(LOG_INFO)<<"normal"<<endl;
  Logger::log(LOG_INFO)<<(this->normal).x<<endl;  
  Logger::log(LOG_INFO)<<(this->normal).y<<endl;  
  Logger::log(LOG_INFO)<<(this->normal).z<<endl;  
  Logger::log(LOG_INFO)<<(this->normal).t<<endl;  

  Logger::log(LOG_INFO)<<"direction"<<endl;
  Logger::log(LOG_INFO)<<ray.getDirection().x<<endl;
  Logger::log(LOG_INFO)<<ray.getDirection().y<<endl;
  Logger::log(LOG_INFO)<<ray.getDirection().z<<endl;
  Logger::log(LOG_INFO)<<ray.getDirection().t<<endl;
  */
  if(nv != 0) { // the ray is not orthogonal to the normal
    float t = (this->normal).scalar(ray.getOrigin() - b) / nv;
    /*Logger::log(LOG_INFO)<<"t"<<endl;
      Logger::log(LOG_INFO)<<t<<endl;*/

    if(t > 0) { // the ray is going to the plane
      Vec4<float> p = ray.getOrigin() + ray.getDirection()*t;
      float c1 = ((b - a) * (p - a)).scalar(this->normal);
      float c2 = ((c - b) * (p - b)).scalar(this->normal);
      float c3 = ((a - c) * (p - c)).scalar(this->normal);
      if((c1 <= 0 && c2 <= 0 && c3 <= 0) ||(c1 >= 0 && c2 >= 0 && c3 >= 0)) { // the intersection is in the triangle
	*distance = t;
	*normal = this->normal;
	*material = &(*(this->material)); // double * are generaly a bad idea, I don't know why it is used.
	//	Logger::log(LOG_INFO)<<"Intersection with a triangle"<<endl;
      } else {
	*distance = -1;
      }
    } else {
      *distance = -1;
    }
  } else {
    *distance = -1;
  }
}

