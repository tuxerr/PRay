#include <string>
#include "logger.h"
#include "server.h"
#include "color.h"
#include "testScenes.h"
#include "display.h"

#define WIDTH 640
#define HEIGHT 480

#define CAM_TRANS_FACTOR  5
#define CAM_ROT_ANGLE     2

int main()
{
    Logger::init("pray_client.log");

    const string standaloneMode ("--test");

    if (true) // if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
        Display::init(WIDTH,HEIGHT);
        Display *disp = &(Display::getInstance());
        
        Color pixel;
        int width = WIDTH;
        int height = HEIGHT;

        // scene loading
        TestScenes testScenes;
        Scene scene = testScenes.createTestScene1(width, height);

        Logger::log(LOG_INFO)<<"Rendering started"<<endl;

        disp->register_keyhook(std::bind(&Camera::translateForward,scene.getCamera()),SDLK_z);
        disp->register_keyhook(std::bind(&Camera::translateBackwards,scene.getCamera()),SDLK_s);
        disp->register_keyhook(std::bind(&Camera::translateRight,scene.getCamera()),SDLK_d);
        disp->register_keyhook(std::bind(&Camera::translateLeft,scene.getCamera()),SDLK_q);
        disp->register_keyhook(std::bind(&Camera::rollLeft,scene.getCamera()),SDLK_a);
        disp->register_keyhook(std::bind(&Camera::rollRight,scene.getCamera()),SDLK_e);
        disp->register_keyhook(std::bind(&Camera::pitchUp,scene.getCamera()),SDLK_UP);
        disp->register_keyhook(std::bind(&Camera::pitchDown,scene.getCamera()),SDLK_DOWN);
        disp->register_keyhook(std::bind(&Camera::yawLeft,scene.getCamera()),SDLK_LEFT);
        disp->register_keyhook(std::bind(&Camera::yawRight,scene.getCamera()),SDLK_RIGHT);

        while ( !disp->quit() )
        {
            for (int y=0 ; y < height ; y++)
            {
                for (int x=0 ; x < width ; x++)
                {
                    pixel = scene.renderPixel(x,y);

                    disp->add_pixel(x,y,pixel);
                }
            }

            disp->refresh_display();

            disp->refresh_controls();

        }

        Logger::log(LOG_INFO)<<"Rendering complete"<<endl;

        Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

        testScenes.destroyTestScene1(scene);
    }

    return EXIT_SUCCESS;
}
