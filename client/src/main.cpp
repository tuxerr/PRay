#include <string>
#include "logger.h"
#include "server.h"
#include "color.h"
#include "display.h"
#include "sceneLoader.h"

#define WIDTH 800
#define HEIGHT 450

#define CAM_TRANS_FACTOR  5
#define CAM_ROT_ANGLE     2

int main(int argc, char* argv[])
{
    string filename;

    Logger::init("pray_client.log");

    if (argc != 2) {
        Logger::log(LOG_ERROR) << "bad arguments" << endl;
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

        while ( !disp->quit() )
        {
            for (int y=0 ; y < height ; y++)
            {
                for (int x=0 ; x < width ; x++)
                {
                    pixel = scene->renderPixel(x,y);

                    disp->add_pixel(x,y,pixel);
                }
            }

            disp->refresh_display();

	    Logger::log(LOG_DEBUG)<<"Frame rendered"<<endl;

            disp->refresh_controls();

        }

        Logger::log(LOG_INFO)<<"Rendering complete"<<endl;

        Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

	delete scene;
    }

    return EXIT_SUCCESS;
}
