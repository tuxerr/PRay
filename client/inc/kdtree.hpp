#ifndef DEF_KDTREE
#define DEF_KDTREE

#include <list>
#include <cfloat>
#include <omp.h>
#include "triangle.hpp"
#include "aabb.hpp"
#include "logger.hpp"

/**
 * kd-tree : axis-aligned binary space partitioning k-dimensional tree
 */
class KdTreeNode {
    friend class Scene;
private:
    std::list<Object*> objects;
    KdTreeNode * left;
    KdTreeNode * right;
    AABB * aabb;
    int depth;
    bool findBestSplit(int axis, float* bestSplit);
    float computeCost(std::list<Object*>* objectsLeft,
                      std::list<Object*>* objectsRight);
    void splitObjects(int axis,
                      std::list<Object*>* objectsNode,
                      std::list<Object*>* objectsLeft,
                      std::list<Object*>* objectsRight);
    void createChildren(int axis, float limit);
    bool terminate();
public :
    KdTreeNode(int depth, AABB* aabb);
    ~KdTreeNode();
    bool isLeaf();
    void addObject(Object* object);
    void computeChildren();
    void getInfos(int* nbNodes, int* nbLeaves, int* nbEmptyLeaves, 
                  float* emptyVolume, int* nbObjets);
};

#endif
