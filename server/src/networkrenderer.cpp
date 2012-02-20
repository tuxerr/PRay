#include "networkrenderer.hpp"

NetworkRenderer::NetworkRenderer(Network &network,Display &disp,NcursesUI &ncursesui) : network(network), display(disp), ncursesui(ncursesui) {
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
    int result_number=0;
    while(1) {
        int id = network.get_first_nonempty_client();
        while (id==-1) {
            network.get_recv_cond().wait();
            id = network.get_first_nonempty_client();
        }
        Client *cl = network.get_client(id);
        string recv = cl->unstack_message();
        
        if(recv=="CALCULATING") {
            rendering_clients[id].status=CLIENT_RENDERING;
        } else if(recv.find("RESULT")==0) {

            stringstream recv_ss(stringstream::in | stringstream::out);
            recv_ss<<recv.substr(6);
            
            parse_network_result_output(recv_ss);
            
            rendering_clients[id].status=CLIENT_WAITING;
            int sent_task = send_task_to_client(id);

            stringstream newstring(stringstream::in);
            newstring<<rendering_clients[id].hostname;
            if(sent_task!=-1) {
                newstring<<" // "<<sent_task;
            }
            ncursesui.get_clients_win()->modify_string(
                rendering_clients[id].curses_id,
                newstring.str());
                                    

            result_number++;
            if(result_number==rendering_task_number) {
                rstatus=RENDERER_WAITING;
                display.refresh_display();
            }

        } else if(recv.find("LOGIN")==0) {
            Rendering_Client newcl;
            newcl.status=CLIENT_WAITING;
            newcl.hostname=recv.substr(6);
            newcl.curses_id=ncursesui.get_clients_win()->add_string(newcl.hostname);
            rendering_clients.insert(rendering_clients.begin()+id,newcl);
        }
    }
}

void NetworkRenderer::set_rendering_file(string xmlfile) {
    if(rstatus==RENDERER_RENDERING) {
        Logger::log(LOG_WARNING)<<"A render is in progress"<<std::endl;
    } else if(rstatus==RENDERER_WAITING) {
        string tosend("SETSCENE ");
        tosend.append(xmlfile);
        network.send_to_all(tosend);
    }
}

void NetworkRenderer::render(int width,int height) {
    if(rstatus==RENDERER_RENDERING) {
        Logger::log(LOG_WARNING)<<"A render is in progress"<<std::endl;
    } else if(rstatus==RENDERER_WAITING) {
        rendering_width=width;
        rendering_height=height;
        rstatus=RENDERER_RENDERING;
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
        rendering_task_number=network_tasks.size();

        Logger::log()<<"Rendering started : "<<width<<"x"<<height<<std::endl;
        for(int i : network.get_client_ids()) {
            send_task_to_client(i);
        }

    }
}

void NetworkRenderer::parse_network_result_output(stringstream &recv_ss) {
    int packet_number;
    recv_ss>>packet_number;
    std::vector<Color> result;
    while(recv_ss.peek()!=EOF) {
        float r,g,b;
        recv_ss>>r>>g>>b;
        Color c(r,g,b);
        result.push_back(c);
    }
    display.add_surface(0,CLIENT_TASK_LINES*packet_number,rendering_width,result.size()/rendering_width,result);
    display.refresh_part_display_timecheck();
}

int NetworkRenderer::send_task_to_client(int id) {
    if(!network_tasks.empty()) {
        Task currenttask = network_tasks.back();
        network_tasks.erase(network_tasks.end()-1);

        Client* cl = network.get_client(id);
        stringstream send(stringstream::in | stringstream::out);
        send<<"CALCULATE "<<network_tasks.size()<<""<<currenttask.y<<" "<<currenttask.width<<" "<<currenttask.height;
        cl->send_message(send.str());
        return network_tasks.size();
    } 
    return -1;
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
