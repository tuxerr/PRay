#ifndef NETWORK_RENDERER
#define NETWORK_RENDERER

#include "network.hpp"
#include "logger.hpp"
#include <iostream>
#include "color.hpp"
#include <vector>
#include <string>
#include <pthread.h>
#include <sstream>

#define CLIENT_TASK_LINES 2

typedef enum {
    RENDERER_WAITING,
    RENDERER_RENDERING
} Render_Status;

typedef enum {
    CLIENT_WAITING,
    CLIENT_RENDERING
} Client_Status;

typedef struct {
    int y;
    int width;
    int height;
} Task;

typedef struct {
    string hostname;
    Client_Status status;
} Rendering_Client;

class NetworkRenderer {
public:
    NetworkRenderer(Network &network);
    void renderer_thread();
    void set_rendering_file(string xmlfile);
    void send_task_to_client(int id);
    std::vector<Color> render(int width,int height);

    static void* launch_renderer_thread(void *This);

    void camera_translate_forward();
    void camera_translate_backwards();
    void camera_translate_left();
    void camera_translate_right();
    void camera_translate_up();
    void camera_translate_down();
    void camera_roll_left();
    void camera_roll_right();
    void camera_pitch_up();
    void camera_pitch_down();
    void camera_yaw_left();
    void camera_yaw_right();
    void camera_switch_mode();

private:    
    pthread_t thread;
    Network &network;
    Render_Status rstatus;
    std::vector<Task> network_tasks;
    std::vector<Rendering_Client> rendering_clients;
    std::vector< std::vector < Color >* > results;
    int rendering_task_number;

    void send_task_to_client(int id);

};

#endif
