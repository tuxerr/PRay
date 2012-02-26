#include "kdtree.hpp"

#define NODE_DEPTH_LIMIT 15
#define NODE_OBJECTS_LIMIT 3
#define NODE_SIZE_LIMIT 0.001

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

bool KdTreeNode::terminate()
{
    return depth > NODE_DEPTH_LIMIT 
        || objects.size() < NODE_OBJECTS_LIMIT
        || std::min(aabb->maxX - aabb->minX, 
                    std::min(aabb->maxY - aabb->minY, 
                             aabb->maxZ - aabb->minZ)) < NODE_SIZE_LIMIT;
}

void KdTreeNode::computeChildren()
{
    int axis = depth % 3;

    if (terminate()) { // the node is a leaf
        return;
    }

    float limit;
    if (! findBestSplit(axis, &limit)) return;
    createChildren(axis, limit);
    splitObjects(axis, &objects, &(left->objects), &(right->objects));
    objects.clear(); // only leaves keep their objects

    left->computeChildren();
    right->computeChildren();
}

/**
 * Local greedy surface area heuristic
 *
 * TODO : The accurate way of determining the candidate planes thus is
 * to first clip the triangle t to the voxel V , and use the sides of
 * the clipped triangle’s AABB B(t ∩ V )
 */
bool KdTreeNode::findBestSplit(int axis, float* bestSplit)
{
    float cost, bestCost = FLT_MAX;
    std::list<float> limits;

    std::list<Object*>::iterator iterObj;
    AABB * aabb;

    for (iterObj = objects.begin(); iterObj != objects.end(); iterObj++)
    {
        aabb = (*iterObj)->getAABB();

        if (axis == 0) {        // X
            limits.push_back(aabb->minX);
            limits.push_back(aabb->maxX);
        } else if (axis == 1) { // Y
            limits.push_back(aabb->minY);
            limits.push_back(aabb->maxY);
        } else {                // Z
            limits.push_back(aabb->minZ);
            limits.push_back(aabb->maxZ);
        }
    }

    limits.sort();
    limits.unique();

    float thisMin, thisMax;

    if (axis == 0) {        // X
        thisMin = this->aabb->minX;
        thisMax = this->aabb->maxX;
    } else if (axis == 1) { // Y
        thisMin = this->aabb->minY;
        thisMax = this->aabb->maxY;
    } else {                // Z
        thisMin = this->aabb->minZ;
        thisMax = this->aabb->maxZ;
    }

    //Logger::log(LOG_DEBUG)<<"limit list size = "<<limits.size()<<std::endl;

    std::list<Object*> objectsNode;
    std::list<Object*> objectsLeft;
    std::list<Object*> objectsRight;

    objectsNode.assign(objects.begin(), objects.end());

    bool splitFound = false;

    std::list<float>::iterator iterLimit;

    for (iterLimit = limits.begin(); iterLimit != limits.end(); iterLimit++)
    {
        if (thisMin < *iterLimit && *iterLimit < thisMax) {
            splitFound = true;

            //Logger::log(LOG_DEBUG)<<"----------------------------"<<std::endl;
            //Logger::log(LOG_DEBUG)<<"limit candidate = "<<*iterLimit<<std::endl;

            createChildren(axis, *iterLimit);
            splitObjects(axis, &objectsNode, &objectsLeft, &objectsRight);

            cost = computeCost(&objectsLeft, &objectsRight);
            //Logger::log(LOG_DEBUG)<<"cost = "<<cost<<std::endl;
            if (cost < bestCost) *bestSplit = *iterLimit;

            objectsNode.clear();
            objectsNode.splice(objectsNode.begin(), objectsRight);                          

            if (left != NULL) delete left;
            if (right != NULL) delete right;
        }
    }
    
    //Logger::log(LOG_DEBUG)<<"bestSplit = "<<*bestSplit<<std::endl;

    return splitFound;
}

float KdTreeNode::computeCost(std::list<Object*>* objectsLeft,
                              std::list<Object*>* objectsRight)
{
    if (isLeaf()) {
        return aabb->surfaceArea * objects.size();
    }

    float lo = objectsLeft->size();
    float ro = objectsRight->size();

    if (lo == 0)
        return 0.8 * right->aabb->surfaceArea * ro;

    if (ro == 0)
        return 0.8 * left->aabb->surfaceArea * lo;

    return left->aabb->surfaceArea * lo + right->aabb->surfaceArea * ro;
} 

void KdTreeNode::createChildren(int axis, float limit)
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
}

void KdTreeNode::splitObjects(int axis, 
                              std::list<Object*>* objectsNode,
                              std::list<Object*>* objectsLeft,
                              std::list<Object*>* objectsRight)
{
    std::list<Object*>::iterator iterObj;
    AABB * aabb;

    for (iterObj = objectsNode->begin(); iterObj != objectsNode->end(); iterObj++)
    {
        aabb = (*iterObj)->getAABB();
     
        switch (axis) {
        case 0: // X
            if (aabb->minX < left->aabb->maxX)
                objectsLeft->push_back(*iterObj);
            if (aabb->maxX > right->aabb->minX)
                objectsRight->push_back(*iterObj);
            break;
        case 1: // Y
            if (aabb->minY < left->aabb->maxY)
                objectsLeft->push_back(*iterObj);
            if (aabb->maxY > right->aabb->minY)
                objectsRight->push_back(*iterObj);
            break;
        case 2: // Z
            if (aabb->minZ < left->aabb->maxZ)
                objectsLeft->push_back(*iterObj);
            if (aabb->maxZ > right->aabb->minZ)
                objectsRight->push_back(*iterObj);
            break;
        default: // error
            break;
        }
    }
}

void KdTreeNode::getInfos(int* nbNodes, int* nbLeaves, int* nbEmptyLeaves, 
                          float* emptyVolume, int* nbObjets)
{
/*
    Logger::log(LOG_DEBUG)<<"Node : addr    = "<<this<<std::endl; 
    Logger::log(LOG_DEBUG)<<"       depth   = "<<depth<<std::endl;
    Logger::log(LOG_DEBUG)<<"       left    = "<<left<<std::endl;
    Logger::log(LOG_DEBUG)<<"       right   = "<<right<<std::endl;
    Logger::log(LOG_DEBUG)<<"       objects = "<<objects.size()<<std::endl;
*/
    //Logger::log(LOG_DEBUG)<<"volume = "<<aabb->getVolume()<<std::endl;

    if (isLeaf()) {
        *nbNodes = 1;
        *nbLeaves = 1;
        *nbEmptyLeaves = (objects.empty() ? 1 : 0);
        *emptyVolume = (objects.empty() ? aabb->getVolume() : 0.0);
        *nbObjets = objects.size();
    } else {
        int nbNodesLeft, nbLeavesLeft, nbEmptyLeavesLeft, nbObjetsLeft;
        int nbNodesRight, nbLeavesRight, nbEmptyLeavesRight, nbObjetsRight;
        float emptyVolumeLeft, emptyVolumeRight;

        left->getInfos(&nbNodesLeft, &nbLeavesLeft, &nbEmptyLeavesLeft, 
                       &emptyVolumeLeft, &nbObjetsLeft);
        right->getInfos(&nbNodesRight, &nbLeavesRight, &nbEmptyLeavesRight, 
                        &emptyVolumeRight, &nbObjetsRight);
        *nbNodes = 1 + nbNodesLeft + nbNodesRight;
        *nbLeaves = nbLeavesLeft + nbLeavesRight;
        *nbEmptyLeaves = nbEmptyLeavesLeft + nbEmptyLeavesRight;
        *emptyVolume = emptyVolumeLeft + emptyVolumeRight;
        *nbObjets = nbObjetsLeft + nbObjetsRight;
    }
}
