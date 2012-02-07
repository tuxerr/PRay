#include "testScenes.h"
#include "uglyMaterial.h"
#include "phongMaterial.h"
#include "object.h"
#include "color.h"
#include "sphere.h"
#include "triangle.h"
#include "directionalLight.h"
#include "ambientLight.h"
#include "vec3.h"

Scene TestScenes::createTestScene1(int xRes, int yRes)
{
  list<Object*> objects;

    objects.push_back(new Sphere(Vec3<float>(100,-6, 0), 3, new UglyMaterial(Color(255,   0,   0)))); // red
    objects.push_back(new Sphere(Vec3<float>(100, 0, 0), 3, new UglyMaterial(Color(  0, 255,   0)))); // green
    objects.push_back(new Sphere(Vec3<float>(100, 6, 0), 3, new PhongMaterial(Color(  0,   100, 255), 0.6, 0.5, 0.4, 100))); // blue~
    objects.push_back(new Sphere(Vec3<float>( 90,-1, 0), 1, new UglyMaterial(Color(255,   0, 255)))); // violet
    objects.push_back(new Sphere(Vec3<float>(100, 3, 3), 2, new UglyMaterial(Color(255, 127,   0)))); // orange

    Vec3<float> a = Vec3<float>(100, 6, 1); // the triangle should be visible
    Vec3<float> b = Vec3<float>(100, 0, 1);
    Vec3<float> c = Vec3<float>( 95, 3, 5);
    objects.push_back(new Triangle(a,b,c,new UglyMaterial(Color(255, 255, 255)))); // white

    list<DirectionalLight> lDirLights;

    lDirLights.push_back(DirectionalLight(255.0, (Vec3<float> (-1, -0.5, 0)).normalize()));

    Camera* camera = new Camera(Vec3<float>(0,0,0), // center
                                Vec3<float>(1,0,0), // direction
                                Vec3<float>(0,0,1), // normal
                                16/2, 9/2,
                                35,
                                xRes, yRes);

    return Scene(objects,lDirLights,AmbientLight(),camera);
}

void TestScenes::destroyTestScene1(Scene scene)
{
    list<Object*> objects = scene.getObjects();

    list<Object*>::iterator iter;

    for (iter = objects.begin() ; iter != objects.end() ; iter++) {
        delete *iter;
    }
}

/*
Scene TestScenes::getTestScene2()
{
    //PhongMaterial sphereMaterial(Color(124,200,62), 0.4, 0.2, 0.6, 0.1);
    UglyMaterial sphereMaterial(Color(124,200,62));

    list<Object> objects;

    for (int x = 0 ; x < 100 ; x += 10)
        for (int y = 0 ; y < 100 ; y += 10)
            for (int z = 0 ; z < 100 ; z += 10)
                objects.push_back(Sphere(Vec3<float>(x, y, z), 3, &sphereMaterial));

    list<DirectionalLight> lDirLights;
    lDirLights.push_back(DirectionalLight(20,
					  Color(255,255,200),
					  Vec3<float>(1, 1, -1)));

    Camera camera(Vec3<float>(-20, -20, 30),
                  Vec3<float>(2, 2, -1),
                  Vec3<float>(-1, -1, 2),
                  16,9,
                  5,
                  800,450);

    return Scene(objects,
		 lDirLights,
                 AmbientLight(),
                 camera);
}
*/
