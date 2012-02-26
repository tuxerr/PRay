#include "scene.hpp"

Scene::Scene(const list<Object*> objects,
             const list<Light*> lights,
             const set<Material*> materials,
             const AmbientLight &ambientLight,
             Camera* camera) :
    objects(objects),
    lights(lights),
    materials(materials),
    ambientLight(ambientLight),
    camera(camera),
    kdTree(NULL)
{
    if (Settings::getAsBool("use_kdtree")) {
        computeKdTree();
    }
}

Scene::~Scene()
{
    list<Object*>::iterator iterObj;

    for (iterObj = objects.begin() ; iterObj != objects.end() ; iterObj++) {
        delete *iterObj;
    }

    set<Material*>::iterator iterMat;

    for (iterMat = materials.begin() ; iterMat != materials.end() ; iterMat++) {
        delete *iterMat;
    }

    list<Light*>::iterator iterLights;

    for (iterLights = lights.begin() ; iterLights != lights.end() ; iterLights++) {
        delete *iterLights;
    }

    delete camera;

    if (Settings::getAsBool("use_kdtree")) {
        delete kdTree;
    }
}

list<Object*> Scene::getObjects() {
    return objects;
}

list<Light*> Scene::getLights() {
    return lights;
}

AmbientLight Scene::getAmbientLight() {
    return ambientLight;
}

Camera* Scene::getCamera() {
    return camera;
}

Color Scene::renderRay(Ray &ray) {
    float distance = -3;
    VEC3F normal;
    Material* material = 0;

    computeIntersection(ray, &distance, &normal, &material);

    if (distance < 0) { // no intersection was found
        return Color(0,0,0);
    } else {
        if (material == 0) return Color(255,0,255); // DEBUG kdtree

        Color result = material->renderRay(ray, distance, normal, this);
        // for(int i=0; i<5; i++) {
        //     result = result.merge(material->renderRay(ray, distance, normal, this));
        // }
        return result;
    }
}

AABB* Scene::computeGlobalAABB()
{
    float minX = FLT_MAX, maxX = FLT_MIN;
    float minY = FLT_MAX, maxY = FLT_MIN;
    float minZ = FLT_MAX, maxZ = FLT_MIN;

    list<Object*>::iterator iterObj;
    AABB * aabb;

    for (iterObj = objects.begin(); iterObj != objects.end(); iterObj++)
    {
        aabb = (*iterObj)->getAABB();
        minX = min(minX, aabb->minX);
        maxX = max(maxX, aabb->maxX);
        minY = min(minY, aabb->minY);
        maxY = max(maxY, aabb->maxY);
        minZ = min(minZ, aabb->minZ);
        maxZ = max(maxZ, aabb->maxZ);
    }

    return new AABB(minX, maxX, minY, maxY, minZ, maxZ);
}

void Scene::computeKdTree()
{
    Logger::log(LOG_INFO)<<"Start building kd-tree"<<endl;

    AABB* globalAABB = computeGlobalAABB();

    kdTree = new KdTreeNode(0, globalAABB);

    list<Object*>::iterator iterObj;

    for (iterObj = objects.begin(); iterObj != objects.end(); iterObj++)
    {
        kdTree->addObject(*iterObj);
    }

    kdTree->computeChildren();

    int nbNodes, nbLeaves, nbEmptyLeaves, nbObjets;
    float emptyVolume;
    kdTree->getInfos(&nbNodes, &nbLeaves, &nbEmptyLeaves, &emptyVolume, &nbObjets);

    Logger::log(LOG_INFO)<<" - number of nodes : "<<nbNodes<<endl;
    Logger::log(LOG_INFO)<<" - number of leaves : "<<nbLeaves<<endl;
    Logger::log(LOG_INFO)<<" - number of empty leaves : "<<nbEmptyLeaves<<endl;
    Logger::log(LOG_INFO)<<" - number of objects : "<<nbObjets<<endl;
    Logger::log(LOG_INFO)<<" - empty volume : "<< 100.0 * emptyVolume / kdTree->aabb->getVolume() <<"%"<<endl;
    Logger::log(LOG_INFO)<<"Kd-tree building completed"<<endl;
}

KdTreeNode* Scene::getKdTree()
{
    return kdTree;
}

void Scene::computeIntersectionNode(KdTreeNode *node,
                                    Ray &ray,
                                    float *distance,
                                    VEC3F *normal,
                                    Material **material)
{
    if (node->isLeaf()) {
        *distance = -2;
        float tempDistance = -1;
        VEC3F tempNormal;
        Material* tempMaterial;
        list<Object*>::iterator iter;

        for (iter = node->objects.begin(); iter != node->objects.end(); iter++)
        {
            (*iter)->getIntersection(ray, &tempDistance, &tempNormal, &tempMaterial);

            // Fixes the precision problem for shadows.
            if(-0.001 < tempDistance && tempDistance < 0 ) {
                tempDistance = -tempDistance;
            }
            // ----------------------------------------

            if (tempDistance >= 0
                && ((*distance >= 0 && tempDistance < *distance)
                    || *distance < 0 ))
            {
                *distance = tempDistance;
                *normal = tempNormal;
                *material = tempMaterial;
            }

            tempDistance = -1;
        }

    } else {
        float left_distance = -1, right_distance = -1;
        VEC3F left_normal, right_normal;
        Material *left_material = 0, *right_material = 0;

        if (node->left->aabb->intersectRay(ray)) {
            computeIntersectionNode(node->left, ray, &left_distance, &left_normal, &left_material);
        }
        if (node->right->aabb->intersectRay(ray)) {
            computeIntersectionNode(node->right, ray, &right_distance, &right_normal, &right_material);
        }

        if (-1 < left_distance) {
            if (-1 < right_distance) {
                if (left_distance < right_distance) {
                    *distance = left_distance;
                    *normal = left_normal;
                    *material = left_material;
                    return;
                } else {
                    *distance = right_distance;
                    *normal = right_normal;
                    *material = right_material;
                    return;
                }
            } else {
                *distance = left_distance;
                *normal = left_normal;
                *material = left_material;
                return;
            }
        } else {
            if (-1 < right_distance) {
                *distance = right_distance;
                *normal = right_normal;
                *material = right_material;
                return;
            } else {
                *distance = -1;
                *normal = 0;
                *material = 0;
                return;
            }
        }
    }
}

/**
 * *distance < 0 if no intersection was found
 */
void Scene::computeIntersection(Ray &ray, float *distance, VEC3F *normal,
                                Material **material)
{
    if (Settings::getAsBool("use_kdtree")) {

        computeIntersectionNode(kdTree, ray, distance, normal, material);

    } else {
        *distance = -2;
        float tempDistance = -1;
        VEC3F tempNormal;
        Material* tempMaterial;
        list<Object*>::iterator iter;

        for (iter = objects.begin(); iter != objects.end(); iter++)
        {
            (*iter)->getIntersection(ray, &tempDistance, &tempNormal, &tempMaterial);

            // Fixes the precision problem for shadows.
            if(tempDistance < 0 && tempDistance > -0.001) {
                tempDistance = -tempDistance;
            }
            // ----------------------------------------

            if (tempDistance >= 0
                && ((*distance >= 0 && tempDistance < *distance)
                    || *distance < 0 ))
            {
                *distance = tempDistance;
                *normal = tempNormal;
                *material = tempMaterial;
            }

            tempDistance = -1;
        }
    }
}

/**
 * Adaptive stochastic supersampling
 */
Color Scene::renderPixel(int x, int y) {

    VEC3F origin = camera->getPoint();

    if (Settings::getAsBool("supersampling_enable")) {

        int launchedRays = 0;
        std::vector<VEC3F> directions;
        std::vector<Color> colors;
        float mean_r=0, mean_g=0, mean_b=0;
        float old_mean_r, old_mean_g, old_mean_b;

        directions = camera->getFourDirections(x, y);
        for (int i = 0 ; i < 4 ; i++) {
            Color color;
            Ray ray = Ray(origin, directions[i], color);
            Color res = renderRay(ray);
            launchedRays++;
            colors.push_back(res);
            mean_r += res.getR();
            mean_g += res.getG();
            mean_b += res.getB();
        }
        mean_r /= 4;
        mean_g /= 4;
        mean_b /= 4;

        bool doSupersampling = false;

        for (int i = 0 ; i < 4 ; i++) {
            if (fabs(mean_r - colors[i].getR())
                + fabs(mean_g - colors[i].getG())
                + fabs(mean_b - colors[i].getB())
                > Settings::getAsFloat("supersampling_threshold_start")) {
                doSupersampling = true;
                break;
            }
        }

        if (doSupersampling) {
            do {
                old_mean_r = mean_r;
                old_mean_g = mean_g;
                old_mean_b = mean_b;

                mean_r *= launchedRays;
                mean_g *= launchedRays;
                mean_b *= launchedRays;

                directions.clear();
                directions = camera->getFourDirections(x, y);
                for (int i = 0 ; i < 4 ; i++) {
                    Color color;
                    Ray ray = Ray(origin, directions[i], color);
                    Color res = renderRay(ray);
                    launchedRays++;
                    mean_r += res.getR();
                    mean_g += res.getG();
                    mean_b += res.getB();
                }

                mean_r /= launchedRays;
                mean_g /= launchedRays;
                mean_b /= launchedRays;

            } while ((launchedRays < Settings::getAsInt("supersampling_max_rays"))
                     && (fabs(old_mean_r - mean_r)
                         + fabs(old_mean_g - mean_g)
                         + fabs(old_mean_b - mean_b)
                         > Settings::getAsFloat("supersampling_threshold_end")));
        }
        /*
          if (launchedRays > 4) {
          Logger::log(LOG_DEBUG)<<"launchedRays="<<launchedRays<<endl;
          }
        */
        if (Settings::getAsBool("supersampling_show")) {
            return Color(min((float)1.0, (float)(launchedRays - 4)
                             / Settings::getAsFloat("supersampling_show_limit")));
        } else {
            return Color(mean_r, mean_g, mean_b);
        }

    } else {
        VEC3F direction = camera->getDirection(x, y);
        Color color;
        Ray ray = Ray(origin, direction, color);
        return renderRay(ray);
    }
}

/**
 * Give the lights that are visible from a point. Used for shadows.
 */
list<Light *> Scene::visibleLights(VEC3F point, float intensity) {

    float distance = -1;
    VEC3F normal;
    Material *material;
    Color color = Color(0.0);
    list<Light *> result;
    Ray ray = Ray(point, normal, color);

    list<Light *>::iterator itLight;
    VEC3F lightDirection;
    VEC3F one = VEC3F(1,1,1);

    for (itLight = lights.begin(); itLight != lights.end(); itLight++) {


        lightDirection = (*itLight)->getDirection(point)*(-1);
        lightDirection = (lightDirection + one*((((float)rand() / (float)RAND_MAX) -0.5)*intensity)).normalize();


        ray = Ray(point, lightDirection, color);
        computeIntersection(ray, &distance, &normal, &material);
        //  Logger::log(LOG_DEBUG)<< distance <<endl;
        if(distance < 0) {
            result.push_back(*itLight);
        }
    }

    return result;
}
