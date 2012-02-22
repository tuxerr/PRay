#include "kdtree.hpp"

KdTreeNode::KdTreeNode(int depth, AABB* aabb) :
    aabb(aabb),
    depth(depth)
{
}

KdTreeNode::~KdTreeNode()
{
    delete left;
    delete right;
    delete aabb;
}

bool KdTreeNode::isLeaf()
{
    return left == NULL 
        && right == NULL; 
}

void KdTreeNode::addObject(Object* object)
{
    return objects.push_back(object);
}

void KdTreeNode::computeChildren()
{
    int axis = depth % 3;
    float limit = findBestSplit(axis);
    split(axis, limit);
}

float KdTreeNode::findBestSplit(int axis)
{
    // TODO
    return 0;
}

void KdTreeNode::split(int axis, float limit)
{
    // TODO
}
