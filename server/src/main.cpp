#include "logger.hpp"
#include "ncursesui.hpp"
#include "network.hpp"
#include "networkrenderer.hpp"
#include <ostream>
#include <unistd.h>
#include <signal.h>
#include "color.hpp"
#include "display.hpp"
#include "settings.hpp"
#include <getopt.h>

#define LOG_PATH "pray_server.log"

using namespace std;

int main(int argc, char *argv[])
{
    Logger::init(LOG_PATH);
    Settings::init("settings.xml");

    static struct option long_options[] = {
                   {"port",       required_argument, 0,  'p' },
                   {0,            0,                 0,  0 }
    };
    int port=0;
    string usage="Usage : ./pray_server --port=PORT";
    string current_option;
    char res='a';
    int option_index=0;

    while((res=getopt_long(argc,argv,"p:",long_options,&option_index))!=-1) {
        switch (res) {
        case 0:
            current_option = string(long_options[option_index].name);
            if(current_option=="port") {
                port=atoi(optarg);
            }
            break;
            
        case '?':
            cout<<usage<<endl;
            break;

        case 'p':
            port=atoi(optarg);
            break;

        default:
            break;
        }
    }

    if(port==0) {
        cout<<usage<<endl;
        exit(EXIT_FAILURE);
    }
    
    Network network(port);
    network.launch();

    Display::init(Settings::getAsInt("window_width"),
                  Settings::getAsInt("window_height"));
    Display *disp = &(Display::getInstance());
    disp->refresh_display();

    NcursesUI ui;
    ui.init();

    NetworkRenderer networkRenderer(network,*disp,ui);

    ui.run();

    network.stop();

    return 0;
}
