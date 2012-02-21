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

    while(serv.is_connected()) {
        serv.wait_for_message();
        string mes = "";
        if(serv.has_messages()) {
            mes=serv.unstack_message();
        }

        /*message parsing*/
        if(mes.find("SETSCENE")==0) {
            string filexml=mes.substring(9);
            sceneLoader.load(filexml,&scene);
            
        } else if(mes.find("CALCULATE")==0) {
            string result_message;
            serv.send_message("CALCULATING");

            serv.send_message(result_message);
        } else if(mes.find("INFO")==0) { 

        } else if(mes.find("CAM")==0) {
            string cam_operation=mes.substring(4);
            if(cam_operation=="tF") {

            } else if(cam_operation=="tB") {

            } else if(cam_operation=="tL") {

            } else if(cam_operation=="tR") {

            } else if(cam_operation=="tU") {

            } else if(cam_operation=="tD") {

            } else if(cam_operation=="rL") {

            } else if(cam_operation=="rR") {

            } else if(cam_operation=="pU") {

            } else if(cam_operation=="pD") {

            } else if(cam_operation=="yL") {

            } else if(cam_operation=="yR") {

            } else if(cam_operation=="sM") {

            } 
        }

    }
    
}


