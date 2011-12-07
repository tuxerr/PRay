#include "logger.h"
#include <ostream>

using namespace std;

int main(int argv, char *argc[])
{
    Logger log;
    NcursesUI ui;

    log.init();
    ui.init(log);

    int lul=2;
    log<<"hi"<<" stackoverflow"<<lul;
//    log<<"salut les bitches"<<"HaHaHAHAHAHAHAHAHAH"<<2<<3.51<<endl;

    ui.run();
    
    log<<lul;

    return 0;
}
