#include "kdtree.hpp"

KdTreeNode::KdTreeNode(KdTreeNode * left, KdTreeNode * right) :
    left(left),
    right(right)
{
}

void KdTreeNode::isLeaf()
{
    return left == NULL 
        && right == NULL; 
}
