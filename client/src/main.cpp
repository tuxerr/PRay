#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "logger.h"
#include "color.h"
#include "testScenes.h"

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


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

        for (int i=0 ; i < height ; i++)
        {
            for (int j=0 ; j < width ; j++)
            {
                pixel = scene.renderPixel(i,j);

                if ( SDL_MUSTLOCK(screen) ) {
                    if ( SDL_LockSurface(screen) < 0 ) {
                        Logger::log(LOG_ERROR)<<"Can't lock screen: "<<SDL_GetError()<<endl;
                        exit(EXIT_FAILURE);
                    }
                }

                putpixel(screen, i, j, 
                         SDL_MapRGB(screen->format, pixel.getR(), 
                                    pixel.getG(), pixel.getB()));

                if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
                
                SDL_UpdateRect(screen, i, j, 1, 1); // SDL_Flip(screen);
            }

            Logger::log(LOG_INFO)<<"Line #"<<i<<" rendered"<<endl;
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


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
    switch(bpp) {
    case 1:
        *p = pixel;
        break;
 
    case 2:
        *(Uint16 *)p = pixel;
        break;
 
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
 
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
