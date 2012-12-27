#include <string>
#ifdef __LINUX__
# include <getopt.h>
#endif
#ifdef _WIN32
# include <windows.h>
#endif
#include "logger.hpp"
#include "server.hpp"
#include "color.hpp"
#include "display.hpp"
#include "sceneLoader.hpp"
#include "renderer.hpp"
#include "settings.hpp"
#include "networkrenderer.hpp"

#define LOG_PATH "pray_client.log"

using namespace std;

void standalone_mode(string filename);
#ifdef __LINUX__
void network_mode(string server_name,int port);
#endif
#ifdef __WIN32__
void usleep(int waitTime);
#endif

int main(int argc, char* argv[])
{
    Logger::init(LOG_PATH);
    Settings::init("settings.xml");
    srand ( time(NULL) );

#ifdef __LINUX__
    static struct option long_options[] = {
        {"standalone", no_argument,       0,  's' },
        {"file",       required_argument, 0,  'f' },
        {"server",     required_argument, 0,  0   },
        {"port",       required_argument, 0,  0   },
        {"fork",       no_argument,       0,  0   },
        {0,            0,                 0,  0   }
    };

    char res='s';
    int option_index=0;
    bool standalone=false;
    bool forking=false;
    string filename="";
    string usage="Usage : ./pray_client --standalone --file=file.xml | ./pray_client --server=IP --port=port [--fork]";
    string server="";
    int port=0;
    string current_option;

    while((res=getopt_long(argc,argv,"sf:",long_options,&option_index))!=-1) {
        switch (res) {
        case 0:
            current_option = string(long_options[option_index].name);
            if(current_option=="standalone") {
                standalone=true;
            } else if(current_option=="file") {
                filename=string(optarg);
            } else if(current_option=="server") {
                server=string(optarg);
            } else if(current_option=="port") {
                port=atoi(optarg);
            } else if(current_option=="fork") {
                forking=true;
            }
            break;

        case '?':
            cout<<usage<<endl;
            break;

        case 's':
            standalone=true;
            break;

        case 'f':
            filename=string(optarg);
            break;


        default:
            break;
        }
    }

    if( (!standalone && ( server=="" || port==0)) || (standalone && (filename==""))) {
        cout<<usage<<endl;
    } else if(standalone) {
        standalone_mode(filename);
    } else {
        if(forking) {
            if(fork()==0) {
                network_mode(server,port);
            }
        } else {
            network_mode(server,port);
        }
    }

#endif

#ifdef __WIN32__

    string usage="Usage : ./pray_client file.xml";

    if (argc != 2) {
        cout<<usage<<endl;
        Logger::log(LOG_ERROR)<<"Bad argument"<<endl;
        exit(EXIT_FAILURE);
    }

    standalone_mode(argv[1]);

#endif

    return EXIT_SUCCESS;
}

void standalone_mode(string filename) {
    Display::init(Settings::getAsInt("window_width"),
                  Settings::getAsInt("window_height"));
    Display *disp = &(Display::getInstance());

    Color pixel;
    int width = disp->get_width();
    int height = disp->get_height();

    SceneLoader sceneLoader;
    Scene* scene;

    if ( sceneLoader.load(filename, &scene, width, height) != 0 ) {
        return;
    }

    Logger::log(LOG_INFO)<<"Rendering started in "<<width<<"x"<<height<<endl;

    disp->register_keyhook(std::bind(&Camera::translateForward,   scene->getCamera()), SDLK_z);
    disp->register_keyhook(std::bind(&Camera::translateBackwards, scene->getCamera()), SDLK_s);
    disp->register_keyhook(std::bind(&Camera::translateRight,     scene->getCamera()), SDLK_d);
    disp->register_keyhook(std::bind(&Camera::translateLeft,      scene->getCamera()), SDLK_q);
    disp->register_keyhook(std::bind(&Camera::translateUp,        scene->getCamera()), SDLK_r);
    disp->register_keyhook(std::bind(&Camera::translateDown,      scene->getCamera()), SDLK_f);
    disp->register_keyhook(std::bind(&Camera::rollLeft,           scene->getCamera()), SDLK_a);
    disp->register_keyhook(std::bind(&Camera::rollRight,          scene->getCamera()), SDLK_e);
    disp->register_keyhook(std::bind(&Camera::pitchUp,            scene->getCamera()), SDLK_UP);
    disp->register_keyhook(std::bind(&Camera::pitchDown,          scene->getCamera()), SDLK_DOWN);
    disp->register_keyhook(std::bind(&Camera::yawLeft,            scene->getCamera()), SDLK_LEFT);
    disp->register_keyhook(std::bind(&Camera::yawRight,           scene->getCamera()), SDLK_RIGHT);
    disp->register_keyhook(std::bind(&Camera::switchMode,         scene->getCamera()), SDLK_m);

    Renderer renderer(scene,disp);

#ifdef __LINUX__
    int numOfCPUs = sysconf(_SC_NPROCESSORS_ONLN);
    Logger::log(LOG_INFO)<<"Number of logical processors : "<<numOfCPUs<<endl;
    if (Settings::getAsBool("one_thread")) numOfCPUs = 1;
#endif

#ifdef __WIN32__
    int numOfCPUs = 4;
#endif

    while ( !disp->quit() )
    {
        if(disp->new_control_press()) {
            renderer.render(0,0,width,height,numOfCPUs,true);
            disp->refresh_display();
        } else {
            usleep(30000);
        }

        disp->refresh_controls();
    }

    Logger::log(LOG_INFO)<<"Rendering terminated"<<endl;

    delete scene;
}

#ifdef __LINUX__
void network_mode(string server_name,int port) {
    Server serv(server_name,port);
    serv.connect();

    NetworkRenderer net_renderer(serv);
    net_renderer.run();
    Logger::log(LOG_INFO)<<"Network rendering terminated"<<endl;
}
#endif

#ifdef __WIN32__
void usleep(int waitTime) {
    __int64 time1 = 0, time2 = 0, freq = 0;

    QueryPerformanceCounter((LARGE_INTEGER *) &time1);
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

    do {
        QueryPerformanceCounter((LARGE_INTEGER *) &time2);
    } while((time2-time1) < waitTime);
}
#endif
