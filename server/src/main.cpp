#include "logger.hpp"
#include "ncursesui.hpp"
#include "network.hpp"
#include <ostream>
#include <unistd.h>
#include <signal.h>
#include "color.hpp"
#include "display.hpp"

using namespace std;

class Test {
public:
    void print() {
        std::cout<<"trolol"<<std::endl;
    }
private:    
};

int main(int argv, char *argc[])
{
    Logger::init("pray_server.log");

    Network network;
    network.launch();

//    Display::init(640,640);
//    Display *disp = &(Display::getInstance());
//    disp->refresh_display();

    NcursesUI ui;
    ui.init();
    ui.run();

/*  while(network.get_client_number()==0) {
        sleep(1);
    }

    while(network.get_client_number()!=0) {
        sleep(2);
        std::vector<int> res = network.get_client_ids();
        Client *cli = network.get_client(res.back());
        cli->send_message("trololololo");
        while(!cli->has_messages() && cli->is_connected());
        std::cout<<"received : "<<cli->unstack_message()<<std::endl;
        }  */

    network.stop();

    return 0;
}

/*
#include "display.hpp"
#include "color.hpp"

int main() {
    Logger::init("pray_server.log");
    Display::init(1280,720);
    Display *disp = &(Display::getInstance());
    std::vector<Color> white;
    std::vector<Color> black;
    std::vector<Color> red;
    std::vector<Color> blue;
    std::vector<Color> green;
    for(int i=0;i<1280*720;i++) {
        white.push_back(Color(1,1,1));
        black.push_back(Color(0,0,0));
        red.push_back(Color(1,0,0));
        blue.push_back(Color(0,1,0));
        green.push_back(Color(0,0,1));
    }

    while(!disp->quit()) {
        disp->add_surface(0,0,1280,720,white);
        disp->refresh_display();
        usleep(10000);

        disp->add_surface(0,0,1280,720,black);
        disp->refresh_display();
        usleep(10000);

        disp->add_surface(0,0,1280,720,red);
        disp->refresh_display();
        usleep(10000);

        disp->add_surface(0,0,1280,720,blue);
        disp->refresh_display();
        usleep(10000);

        disp->add_surface(0,0,1280,720,green);
        disp->refresh_display();
        usleep(10000);
        
        disp->refresh_controls();
    }
}
*/
