#ifndef DEF_KDTREE
#define DEF_KDTREE

#include <list>
#include <cfloat>
#include "triangle.hpp"
#include "aabb.hpp"
#include "logger.hpp"

class KdTreeNode {
    friend class Scene;
private:
    std::list<Object*> objects;
    KdTreeNode * left;
    KdTreeNode * right;
    AABB * aabb;
    int depth;
    float findBestSplit(int axis);
    float computeCost();
    void split(int axis, float limit);
public :
    KdTreeNode(int depth, AABB* aabb);
    ~KdTreeNode();
    bool isLeaf();
    void addObject(Object* object);
    void computeChildren();
};

#endif
