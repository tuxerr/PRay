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
    objects.push_back(object);
}

void KdTreeNode::computeChildren()
{
    int axis = depth % 3;
    float limit = findBestSplit(axis);
    split(axis, limit);
    objects.clear(); // only leaves keep their objects

    if (left != NULL) {
        if (left->depth < 20 and left->objects.size() > 3) {
            left->computeChildren();
        }
    }

    if (right != NULL) {
        if (right->depth < 20 and right->objects.size() > 3) {
            right->computeChildren();
        }
    }
}

/**
 * Local greedy surface area heuristic
 *
 * TODO : The accurate way of determining the candidate planes thus is
 * to first clip the triangle t to the voxel V , and use the sides of
 * the clipped triangle’s AABB B(t ∩ V )
 */
float KdTreeNode::findBestSplit(int axis)
{
    float bestSplit = 0;
    float cost, bestCost = FLT_MAX;

    std::list<Object*>::iterator iterObj;
    AABB * aabb;

    for (iterObj = objects.begin(); iterObj != objects.end(); iterObj++)
    {
        aabb = (*iterObj)->getAABB();

        if (axis == 0) {
            // X
            split(axis, aabb->minX);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->minX;

            split(axis, aabb->maxX);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->maxX;

        } else if (axis == 1) {
            // Y
            split(axis, aabb->minY);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->minY;

            split(axis, aabb->maxY);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->maxY;

        } else {
            // Z
            split(axis, aabb->minZ);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->minZ;

            split(axis, aabb->maxZ);
            cost = computeCost();
            if (cost < bestCost)
                bestSplit = aabb->maxZ;
        }
    }
    
    return bestSplit;
}

float KdTreeNode::computeCost()
{
    if (isLeaf()) {
        return aabb->surfaceArea * objects.size();
    }

    float lo = left->objects.size();
    float ro = right->objects.size();

    if (lo == 0)
        return 0.8 * right->aabb->surfaceArea * ro;

    if (ro == 0)
        return 0.8 * left->aabb->surfaceArea * lo;

    return left->aabb->surfaceArea * lo + right->aabb->surfaceArea * ro;
} 

void KdTreeNode::split(int axis, float limit)
{
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
    }
}

unsigned int KdTreeNode::getNbNodes()
{
/*
    Logger::log(LOG_DEBUG)<<"Node : addr    = "<<this<<std::endl; 
    Logger::log(LOG_DEBUG)<<"       depth   = "<<depth<<std::endl;
    Logger::log(LOG_DEBUG)<<"       left    = "<<left<<std::endl;
    Logger::log(LOG_DEBUG)<<"       right   = "<<right<<std::endl;
    Logger::log(LOG_DEBUG)<<"       objects = "<<objects.size()<<std::endl;
*/
    unsigned int nb_left = 0, nb_right = 0;
    
    if (left != NULL)
        nb_left = left->getNbNodes();

    if (right != NULL)
        nb_right = right->getNbNodes();
        
    return nb_left + nb_right + objects.size();
}
