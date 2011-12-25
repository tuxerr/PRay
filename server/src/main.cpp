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

    sleep(10);

    network.stop();

    return 0;
}
