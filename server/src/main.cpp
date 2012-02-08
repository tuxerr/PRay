#include "logger.h"
#include "ncursesui.h"
#include "network.h"
#include <ostream>
#include <unistd.h>
#include <signal.h>
#include "color.h"
#include "display.h"

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
    } */

    network.stop();

    return 0;
}
