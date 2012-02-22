#ifndef DEF_KDTREE
#define DEF_KDTREE

#include <list>
#include "triangle.hpp"
#include "aabb.hpp"

class KdTreeNode {
private:
    std::List<Object*> objects;
    KdTreeNode * left;
    KdTreeNode * right;
    AABB * aabb;
    int depth;
    float findBestSplit(int axis);
    void split(int axis, float limit);
public :
    KdTreeNode(int depth, AABB* aabb);
    ~KdTreeNode();
    bool isLeaf();
    void addObj(Object* object);
    void computeChildren();
};

#endif
