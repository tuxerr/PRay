#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include <algorithm>
#include "object.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "logger.hpp"
//#include "vertex.hpp"

//class Vertex;

using namespace std;

class Triangle;

class Vertex {
private:
    vector<Triangle *> facesAround;
public:
    VEC3F coord;
    VEC3F normal;
    Vertex(VEC3F &coord, VEC3F &normal);
    Vertex();
    Triangle* getFacesAroundContaining(Vertex *vertex1, Vertex *vertex2);
};


class Triangle : public Object {
private :
    Vertex *a;
    Vertex *b;
    Vertex *c;
    VEC3F normal;
    VEC3F getNormal(VEC3F &point);
public :
    Triangle(Vertex *a, Vertex *b, Vertex *c,
             VEC3F &normal, Material *material);
    VEC3F getNormal() ;
    bool contains(Vertex *v);
    void getIntersection(Ray &ray, float *distance, VEC3F *normal,
                         Material **material);
};

#endif
