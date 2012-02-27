#ifndef DEF_RENDERER
#define DEF_RENDERER

#include "logger.hpp"
#include "scene.hpp"
#include "color.hpp"
#include "mutex.hpp"
#include "display.hpp"
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
    Renderer(Scene *scene,Display *disp=NULL);
    std::vector<Color> render(int x,int y,int width,int height,int thread_number=DEFAULT_THREAD_NUMBER,bool _onscreen=false);
    void compute_task();
    static void *computing_thread(void *This);
    void set_scene(Scene *newscene);
    
private:
    pthread_t new_thread(int x,int y,int width,int height,std::vector<Color> *pixels);
    
    Mutex tasks_mut;
    std::vector< Task > tasks;
    
    Mutex results_mut;
    std::vector< std::vector < Color >* > results;
    Scene *scene;
    unsigned int frameNumber;
    Display *display;
    bool onscreen;
    float total_time;
};

#endif
