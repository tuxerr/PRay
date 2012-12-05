#include "triangle.hpp"

using namespace std;

//Vertex::Vertex() {}

Vertex::Vertex(VEC3F &coord, VEC3F &normal) : 
    coord(coord), normal(normal) {
}

// VEC3F Vertex::getNormal() {
//   return normal;
// }

// VEC3F Vertex::getCoord() {
//   return coord;
// }

Triangle* Vertex::getFacesAroundContaining(Vertex *vertex1, Vertex *vertex2) {
  for (vector<Triangle *>::iterator it = facesAround.begin(); it!=facesAround.end(); ++it) {
      if((*it)->contains(vertex1) && (*it)->contains(vertex2)) {
	  return *it;
    }
  }
  return nullptr;
}
