#include "object.hpp"

Object::Object(Material* material, AABB* aabb) :
    material(material),
    aabb(aabb)
{

}

Object::~Object()
{
    // materials are shared
    //delete material;
    delete aabb;
}

Material* Object::getMaterial() {
    return material;
}

AABB* Object::getAABB() {
    return aabb;
}
