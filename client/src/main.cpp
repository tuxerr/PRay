#include <string>
#include "logger.h"
#include "server.h"
#include "color.h"
#include "display.h"
#include "sceneLoader.h"
#include "renderer.h"

#define WIDTH 1280
#define HEIGHT 720

#define CAM_TRANS_FACTOR  5
#define CAM_ROT_ANGLE     2

int main(int argc, char* argv[])
{
    string filename;

    Logger::init("pray_client.log");

    if (argc != 2) {
        Logger::log(LOG_ERROR) << "Missing argument" << endl;
        Logger::log(LOG_INFO) << "Usage: " << argv[0] << " scene.xml" << endl;
	return EXIT_FAILURE;
    }

    filename = string(argv[1]);

    const string standaloneMode ("--test");

    if (true) // if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
        Display::init(WIDTH,HEIGHT);
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
        disp->register_keyhook(std::bind(&Camera::logInformations,    scene->getCamera()), SDLK_c);
#endif

        Renderer renderer(scene);

        while ( !disp->quit() )
        {

	  std::vector<Color> res = renderer.render(0,0,width,height);
            disp->add_surface(0,0,width,height,res);  
            disp->refresh_display();
            disp->refresh_controls();
        }

        Logger::log(LOG_INFO)<<"Rendering terminated"<<endl;

	delete scene;
    }

    return EXIT_SUCCESS;
}
