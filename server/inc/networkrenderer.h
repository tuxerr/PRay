#ifndef NETWORK_RENDERER
#define NETWORK_RENDERER

#include "network.h"
#include "logger.h"
#include <iostream>
#include "color.h"
#include <vector>
#include <string>

class NetworkRenderer {
public:
    NetworkRenderer(Network &network);
    void renderer_thread();
    void set_rendering_file(string xmlfile);
    std::vector<Color> render(int width,int height);

    static void* launch_renderer_thread(void *This);

private:    
    Network &network;
}

#endif
