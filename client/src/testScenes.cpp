#include "testScenes.h"
#include "uglyMaterial.h"
#include "object.h"
#include "color.h"
#include "sphere.h"
#include "directionalLight.h"
#include "ambientLight.h"
#include "vec4.h"

Scene TestScenes::createTestScene1()
{
    list<Object*> objects;
    objects.push_back(new Sphere(Vec4<float>(10, -5, 0), 3, new UglyMaterial(Color(255,   0,   0))));
    objects.push_back(new Sphere(Vec4<float>(10,  0, 0), 3, new UglyMaterial(Color(  0, 255,   0))));
    objects.push_back(new Sphere(Vec4<float>(10,  5, 0), 3, new UglyMaterial(Color(  0,   0, 255))));
    objects.push_back(new Sphere(Vec4<float>( 8,  0, 0), 1, new UglyMaterial(Color(255,   0, 255))));

    list<DirectionalLight> lDirLights;

    Camera camera(Vec4<float>(0,0,0), // center
                  Vec4<float>(1,0,0), // direction
                  Vec4<float>(0,1,0), // normal
                  16/2, 9/2,
                  2,
                  800, 450);

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
                objects.push_back(Sphere(Vec4<float>(x, y, z), 3, &sphereMaterial));

    list<DirectionalLight> lDirLights;
    lDirLights.push_back(DirectionalLight(20,
					  Color(255,255,200),
					  Vec4<float>(1, 1, -1)));

    Camera camera(Vec4<float>(-20, -20, 30),
                  Vec4<float>(2, 2, -1),
                  Vec4<float>(-1, -1, 2),
                  16,9,
                  5,
                  800,450);

    return Scene(objects,
		 lDirLights,
                 AmbientLight(),
                 camera);
}
*/
