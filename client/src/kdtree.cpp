#include "kdtree.hpp"

KdTreeNode::KdTreeNode(int depth, AABB* aabb) :
    depth(depth),
    aabb(aabb)
{
}

KdTreeNode::~KdTreeNode()
{
    delete left;
    delete right;
    delete aabb;
}

void KdTreeNode::isLeaf()
{
    return left == NULL 
        && right == NULL; 
}

void KdTreeNode::addObj(Object* object)
{
    return objects.push_back(object);
}

void KdTreeNode::computeChildren()
{
    float limit = findBestSplit(axis);
    split(axis, limit);
}

float KdTreeNode::findBestSplit(int axis)
{
    // TODO
}

void KdTreeNode::split(int axis, float limit)
{
    // TODO
}
