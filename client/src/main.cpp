#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "logger.h"
#include "color.h"
#include "testScenes.h"


int main(int argc, char *argv[])
{
    Logger::init("pray_client.log");

    const string standaloneMode ("--test");

    if (true) // if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
      SDL_Surface *screen = NULL;
      const int width(800);
      const int height(450);
        Color pixel;

        Logger::log(LOG_INFO)<<"Starting client in standalone mode"<<endl;
        
        // scene loading
        TestScenes testScenes;
        Scene scene = testScenes.getTestScene1();

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            Logger::log(LOG_ERROR)<<"Problem during SDL initialisation: "<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        Logger::log(LOG_INFO)<<"SDL initialised"<<endl;
        
        screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
        
        if (screen == NULL)
        {
            Logger::log(LOG_ERROR)<<"Problem during screen initialisation: "<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        SDL_WM_SetCaption("PRay rendering", NULL);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        Logger::log(LOG_INFO)<<"Screen initialised"<<endl;

        Logger::log(LOG_INFO)<<"Rendering started"<<endl;

        for (int y=0 ; y < height ; y++)
        {
            for (int x=0 ; x < width ; x++)
            {
                pixel = scene.renderPixel(x,y);
                
                pixelRGBA(screen, x, y, pixel.getR(), pixel.getG(), pixel.getB(), 255);               
            }

            SDL_Flip(screen);

            Logger::log(LOG_INFO)<<"Line #"<<y<<" rendered"<<endl;
        }

        SDL_Delay(1000);

        Logger::log(LOG_INFO)<<"Rendering complete"<<endl;

        SDL_SaveBMP(screen, "image.bmp");

        Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

        SDL_FreeSurface(screen);
        SDL_Quit();

    }

    return EXIT_SUCCESS;
}
