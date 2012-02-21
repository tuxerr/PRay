#ifndef DEF_KDTREE
#define DEF_KDTREE

#include <list>
#include "triangle.hpp"

class KdTreeNode {
public :
    std::List<Triangle> triangles;
    KdTreeNode * left;
    KdTreeNode * right;
    KdTreeNode(KdTreeNode * left = NULL, KdTreeNode * right = NULL);
    bool isLeaf();
};

#endif
