#ifndef DEF_TESTSCENES
#define DEF_TESTSCENES

#include "scene.h"

class TestScenes {
public:
    Scene createTestScene1(int xRes, int yRes);
    void destroyTestScene1(Scene scene);
    /*Scene getTestScene2();*/
};

#endif // ifndef DEF_TESTSCENES
