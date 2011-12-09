#include "logger.h"
#include "ncursesui.h"
#include <ostream>

using namespace std;

int main(int argv, char *argc[])
{
    Logger::init("pray_server.log");
    Logger::log()<<"salut"<<endl;

    NcursesUI ui;

    ui.init();

    ui.run();

    return 0;
}
