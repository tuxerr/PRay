#include "networkrenderer.hpp"

using namespace std;

NetworkRenderer::NetworkRenderer(Server &serv) : 
    serv(serv), status(CLIENT_WAITING) 
{

}

void NetworkRenderer::run() {
    while(!serv.is_connected() && 
          serv.get_failed_connections()<MAX_FAILED_CONNECTIONS) 
    {
        Logger::log()<<"Waiting for server"<<std::endl;
        sleep(1);
    }
    if(!serv.is_connected()) {
        Logger::log()<<"Connection timeout. Closing client"<<std::endl;
        serv.stop();
        return;
    }

    string login_string="LOGIN ";
    char ptr[40]="";
    gethostname(ptr,40);
    login_string.append(ptr);
    serv.send_message(login_string);

    SceneLoader sceneLoader;
    Scene *scene;
    int global_width,global_height;
    Renderer renderer(scene,NULL);

    int numOfCPUs = sysconf(_SC_NPROCESSORS_ONLN);

    while(serv.is_connected()) {
        if(!serv.has_messages()) {
            serv.wait_for_message();
        }
        string mes = "";
        if(serv.has_messages()) {
            mes=serv.unstack_message();
        }
        stringstream mes_ss(stringstream::in | stringstream::out);
        mes_ss<<mes;

        string head;
        mes_ss>>head;

        /*message parsing*/
        if(head=="SETSCENE") {
            string filexml;
            mes_ss>>filexml;
            sceneLoader.load(filexml,&scene,global_width,global_height);
            renderer.set_scene(scene);
            
        } else if(head=="CALCULATE") {
            serv.send_message("CALCULATING");
            int task_number,y,width,height;
            stringstream result_message(stringstream::out);
            mes_ss>>task_number>>y>>width>>height;

            std::vector<Color> rescol = renderer.render(0,y,width,height,numOfCPUs);
	    Logger::log()<<"Rendering part : "<<0<<"/"<<y<<"/"<<width<<"/"<<height<<std::endl;

            result_message<<"RESULT "<<task_number<<" ";
            for(unsigned int i=0;i<rescol.size();i++) {
                result_message.put((char)((rescol[i].getR())*255));
                result_message.put((char)((rescol[i].getG())*255));
                result_message.put((char)((rescol[i].getB())*255));
            }

            serv.send_message(result_message.str());
        } else if(head=="INFO") { 
            mes_ss>>global_width>>global_height;
        } else if(head=="CAM") {
            string cam_operation;
            mes_ss>>cam_operation;
            if(cam_operation=="tF") {
                scene->getCamera()->translateForward();
            } else if(cam_operation=="tB") {
                scene->getCamera()->translateBackwards();
            } else if(cam_operation=="tL") {
                scene->getCamera()->translateRight();
            } else if(cam_operation=="tR") {
                scene->getCamera()->translateLeft();
            } else if(cam_operation=="tU") {
                scene->getCamera()->translateUp();
            } else if(cam_operation=="tD") {
                scene->getCamera()->translateDown();
            } else if(cam_operation=="rL") {
                scene->getCamera()->rollLeft();
            } else if(cam_operation=="rR") {
                scene->getCamera()->rollRight();
            } else if(cam_operation=="pU") {
                scene->getCamera()->pitchUp();
            } else if(cam_operation=="pD") {
                scene->getCamera()->pitchDown();
            } else if(cam_operation=="yL") {
                scene->getCamera()->yawLeft();
            } else if(cam_operation=="yR") {
                scene->getCamera()->yawRight();
            } else if(cam_operation=="sM") 
{               scene->getCamera()->switchMode();
            } 
        }

    }
    
}


