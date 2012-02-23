#include "kdtree.hpp"

KdTreeNode::KdTreeNode(int depth, AABB* aabb) :
    left(NULL),
    right(NULL),
    aabb(aabb),
    depth(depth)
{
}

KdTreeNode::~KdTreeNode()
{
    if (left != NULL) delete left;
    if (right != NULL) delete right;
    if (aabb != NULL) delete aabb;
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

/**
 * Local greedy surface area heuristic
 */
float KdTreeNode::findBestSplit(int axis)
{
    // TODO
    return 0;
}

void KdTreeNode::split(int axis, float limit)
{
//    if (ça vaut le coup);

    float left_minX = aabb->minX, left_minY = aabb->minY, left_minZ = aabb->minZ;
    float left_maxX = aabb->maxX, left_maxY = aabb->maxY, left_maxZ = aabb->maxZ;

    float right_minX = aabb->minX, right_minY = aabb->minY, right_minZ = aabb->minZ;
    float right_maxX = aabb->maxX, right_maxY = aabb->maxY, right_maxZ = aabb->maxZ;

    switch (axis) {
    case 0: // X
        left_maxX = limit;
        right_minX = limit;
        break;
    case 1: // Y
        left_maxY = limit;
        right_minY = limit;
        break;
    case 2: // Z
        left_maxZ = limit;
        right_minZ = limit;
        break;
    default: // error
        break;
    }

    left = new KdTreeNode(depth + 1, new AABB(left_minX, left_maxX,
                                              left_minY, left_maxY,
                                              left_minZ, left_maxZ));

    right = new KdTreeNode(depth + 1, new AABB(right_minX, right_maxX,
                                               right_minY, right_maxY,
                                               right_minZ, right_maxZ));


    std::list<Object*>::iterator iterObj;
    AABB * aabb;

    for (iterObj = objects.begin(); iterObj != objects.end(); iterObj++)
    {
        aabb = (*iterObj)->getAABB();
     
        switch (axis) {
        case 0: // X
            if (aabb->minX < left->aabb->maxX)
                left->objects.push_back(*iterObj);
            if (aabb->maxX > right->aabb->minX)
                right->objects.push_back(*iterObj);
            break;
        case 1: // Y
            if (aabb->minY < left->aabb->maxY)
                left->objects.push_back(*iterObj);
            if (aabb->maxY > right->aabb->minY)
                right->objects.push_back(*iterObj);
            break;
        case 2: // Z
            if (aabb->minZ < left->aabb->maxZ)
                left->objects.push_back(*iterObj);
            if (aabb->maxZ > right->aabb->minZ)
                right->objects.push_back(*iterObj);
            break;
        default: // error
            break;
        }
        
        delete aabb;
        objects.clear(); // only leaves keep their objects
    }
}
