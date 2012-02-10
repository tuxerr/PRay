#ifndef DEF_RENDERER
#define DEF_RENDERER

#include "logger.h"
#include "scene.h"
#include "color.h"
#include "mutex.h"
#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define DEFAULT_THREAD_NUMBER 8
#define PIXEL_GROUPS 64

typedef struct {
    std::vector< std::pair<int,int> > pixels;
    int task_number;
} Task;

class Renderer {
public:
    Renderer(Scene *scene);
    std::vector<Color> render(int x,int y,int width,int height,int thread_number=DEFAULT_THREAD_NUMBER);
    void compute_task();
    static void *computing_thread(void *This);
    
private:
    pthread_t new_thread(int x,int y,int width,int height,std::vector<Color> *pixels);
    
    Mutex tasks_mut;
    std::vector< Task > tasks;
    
    Mutex results_mut;
    std::vector< std::vector < Color >* > results;
    Scene *scene;

    unsigned int frameNumber;
};

#endif
