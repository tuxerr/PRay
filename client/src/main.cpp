#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "logger.h"
#include "color.h"
#include "testScenes.h"

int main(int argc, char *argv[])
{
    Logger::init("pray_client.log");

    const string standaloneMode ("--standalone");

    if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
        SDL_Surface *screen = NULL;
        const int width(800);
        const int height(600);
        Color pixel;

        Logger::log(LOG_INFO)<<"Starting client in standalone mode"<<endl;
        
        // scene loading
        TestScenes testScenes();
        Scene scene = testScene.getTestScene1();

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
        {
            Logger::log(LOG_ERROR)<<"Problem during SDL initialisation"<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        Logger::log(LOG_INFO)<<"SDL initialised"<<endl;
        
        screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
        
        if (screen == NULL)
        {
            Logger::log(LOG_ERROR)<<"Problem during screen initialisation"<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        SDL_WM_SetCaption("PRay rendering", NULL);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        Logger::log(LOG_INFO)<<"Screen initialised"<<endl;

        Logger::log(LOG_INFO)<<"Rendering started"<<endl;

        for (int j=0 ; j < height ; j++)
        {
            for (int i=0 ; i < width ; i++)
            {
                pixel = scene.renderPixel(i,j);
                putPixel(screen, i, j, SDL_MapRGB(screen->format, pixel.getR(), pixel.getG(), pixel.getB()));
                SDL_Flip(screen);
            }
        }

        SDL_Delay(1000);

        Logger::log(LOG_INFO)<<"Rendering complete"<<endl;

        SDL_SaveBMP(screen, "rendu.bmp");

        Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

        SDL_FreeSurface(screen);
        SDL_Quit();

    }

    return EXIT_SUCCESS;
}


