// #include "quadric.hpp"


// Quadric::Quadric(int/*En fait matrice 4x4*/ matrix, Material* material) :
//     Object(material, NULL), matrix(matrix)
// {
//     aabb = new AABB(-1000, 1000, -1000, 1000, -1000, 1000);
// }

// void Quadric::getIntersection(Ray& ray, float* distance,
// 			      VEC3F* normal, Material** material) {

//     // We are solving the equation :
//     // at² + bt + c, where
    
//     float a = op(ray.getDirection(),matrix, ray.getDirection()); // = d'*M*d
//     float b = 2*op(ray.getDirection(), matrix, ray.getOrigin()); // = 2*d'*M*o
//     float c = op(ray.getOrigin(),matrix, ray.getOrigin()); // = o'*M*o

//     float delta = b*b - 4*a*c;
//     if(delta >= 0) {
// 	float t1 = (-b - sqrt(delta))/(2*a);
// 	float t2 = (-b + sqrt(delta))/(2*a);
// 	*distance = t1 > t2 ? t2 : t1;
// 	*material = this->material;
	
// 	VEC3F point = ray.getOrigin() + ray.getDirection()*(*distance);
// 	float p[];
// 	point.getCoord(p);

// 	*normal = (A*p[0] + B*p[1] + C*p[2] + D,
// 		   B*p[0] + E*p[1] + F*p[2] + G,
// 		   C*p[0] + F*p[1] + H*p[2] + I).normalize();
//     }

// }
