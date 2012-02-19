#include <string>
#include <ctime>
#include "logger.hpp"
#include "server.hpp"
#include "color.hpp"
#include "display.hpp"
#include "sceneLoader.hpp"
#include "renderer.hpp"
#include "settings.hpp"

#define LOG_PATH "pray_client.log"

int main(int argc, char* argv[])
{
    Logger::init(LOG_PATH);
    Settings::init("settings.xml");

    srand ( time(NULL) );

    if (argc != 2) {
        Logger::log(LOG_ERROR) << "Missing argument" << endl;
        Logger::log(LOG_INFO) << "Usage: " << argv[0] << " scene.xml" << endl;
	return EXIT_FAILURE;
    }

    string filename = string(argv[1]);

    const string standaloneMode ("--test");

    if (true) // if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
        Display::init(Settings::getAsInt("window_width"),
		      Settings::getAsInt("window_height"));
        Display *disp = &(Display::getInstance());

        Color pixel;
        int width = disp->get_width();
        int height = disp->get_height();

        SceneLoader sceneLoader;
        Scene* scene;

	if ( sceneLoader.load(filename, &scene, width, height) != 0 ) {
	    return EXIT_FAILURE;
	}

        Logger::log(LOG_INFO)<<"Rendering started in "<<width<<"x"<<height<<endl;

#ifndef __INTEL_COMPILER
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
        //disp->register_keyhook(std::bind(&Camera::logInformations,    scene->getCamera()), SDLK_c);
#else
        Logger::log(LOG_INFO)<<"Keys are disabled"<<endl;
#endif

        Renderer renderer(scene,disp);

        int numOfCPUs = sysconf(_SC_NPROCESSORS_ONLN);
        Logger::log(LOG_INFO)<<"Number of logical processors : "<<numOfCPUs<<endl;
        Logger::log(LOG_INFO)<<"Maximum reflections : "<<Settings::getAsInt("max_reflections")<<endl;
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

    return EXIT_SUCCESS;
}
