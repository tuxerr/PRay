#include "plane.hpp"

Plane::Plane(const VEC3F &normal, const VEC3F &point, Material *material) :
    Object(material, NULL),
    normal(normal), 
    point(point)
{
    aabb = new AABB(-1000,1000,-1000,1000,-1000,1000); // TODO
}

VEC3F Plane::getNormal() {
    return normal;
}

VEC3F Plane::getPoint() {
    return point;
}

void Plane::getIntersection(Ray &ray, float *distance, VEC3F *normal, Material **materialIntersection) {

    (this->normal).printLog();
    (ray.direction).printLog();

    float d = (this->normal).scalar(ray.direction);
    Logger::log(LOG_INFO) << "d" << d << std::endl;
    if(fabs(d) >= 0.0001) {
	float t = (this->normal).scalar(this->point - ray.origin) / d;
	*distance = t; 
	*normal = this->normal;
	*materialIntersection = material;
    }
}
