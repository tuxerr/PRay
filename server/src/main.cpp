#include "logger.h"
#include "ncursesui.h"
#include "network.h"
#include <ostream>

using namespace std;

int main(int argv, char *argc[])
{
    Logger::init("pray_server.log");
    Logger::log()<<"salut"<<endl;
    Network network;
//    network.launch();

    NcursesUI ui;

    ui.init();

    ui.run();

//    network.stop();

    return 0;
}
