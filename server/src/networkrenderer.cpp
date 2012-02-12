#include "networkrenderer.h"

NetworkRenderer::NetworkRenderer(Network &network) : network(network) {
    if(pthread_create(&thread,NULL,launch_renderer_thread,(void*)this)!=0) {
        Logger::log(LOG_ERROR)<<"Couldn't launch network renderer thread"<<std::endl;
    }
}

void *NetworkRenderer::launch_renderer_thread(void *This) {
    NetworkRenderer *rend_ptr = (NetworkRenderer*)This;
    rend_ptr->renderer_thread();
    return NULL;
}

void NetworkRenderer::renderer_thread() {
    
}

void NetworkRenderer::set_rendering_file(string xmlfile) {
    if(rstatus==RENDERING) {
        Logger::log(LOG_WARNING)<<"A render is in progress"<<std::endl;
    } else {
        string tosend("SETSCENE ");
        tosend.append(xmlfile);
        network.send_to_all(tosend);
    }
}

std::vector<Color> NetworkRenderer::render(int width,int height) {
    if(rstatus==RENDERING) {
        Logger::log(LOG_WARNING)<<"A render is in progress"<<std::endl;
    } else {
        network_tasks.clear();
        for(int i=0;i<height;i+=CLIENT_TASK_LINES) {

            Task currenttask;
            currenttask.y=i;
            currenttask.width=width;
            if( i+CLIENT_TASK_LINES>height) {
                currenttask.height=(i+CLIENT_TASK_LINES)-height;
            } else {
                currenttask.height=CLIENT_TASK_LINES;                
            }

            network_tasks.push_back(currenttask);
        }
    }
}

// functions to bind to display keys
void NetworkRenderer::camera_translate_forward() {
    network.send_to_all("CAM tF");
}

void NetworkRenderer::camera_translate_backwards() {
    network.send_to_all("CAM tB");
}

void NetworkRenderer::camera_translate_left() {
    network.send_to_all("CAM tL");    
}

void NetworkRenderer::camera_translate_right() {
    network.send_to_all("CAM tR");    
}

void NetworkRenderer::camera_translate_up() {
    network.send_to_all("CAM tU");    
}

void NetworkRenderer::camera_translate_down() {
    network.send_to_all("CAM tD");    
}

void NetworkRenderer::camera_roll_left() {
    network.send_to_all("CAM rL");    
}

void NetworkRenderer::camera_roll_right() {
    network.send_to_all("CAM rR");    
}

void NetworkRenderer::camera_pitch_up() {
    network.send_to_all("CAM pU");    
}

void NetworkRenderer::camera_pitch_down() {
    network.send_to_all("CAM pD");    
}

void NetworkRenderer::camera_yaw_left() {
    network.send_to_all("CAM yL");    
}

void NetworkRenderer::camera_yaw_right() {
    network.send_to_all("CAM yR");    
}

void NetworkRenderer::camera_switch_mode() {
    network.send_to_all("CAM sM");    
}
