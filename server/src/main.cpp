#include "logger.h"
#include "ncursesui.h"
#include "network.h"
#include <ostream>
#include <unistd.h>

using namespace std;

int main(int argv, char *argc[])
{
    Logger::init("pray_server.log");
    Logger::log()<<"salut"<<endl;
    Network network;
    network.launch();

    while(network.get_client_number()==0) {
        sleep(1);
    }

    while(network.get_client_number()!=0) {
        std::cout<<"waiting for all disc"<<std::endl;
        sleep(1);
    }

    network.stop();

    return 0;
}
