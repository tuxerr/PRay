#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "logger.h"
#include "color.h"
#include "testScenes.h"

#define WIDTH  1280
#define HEIGHT  720


int main(int argc, char *argv[])
{
    Logger::init("pray_client.log");

    const string standaloneMode ("--test");

    if (true) // if (argc > 0 && standaloneMode.compare(argv[0]) == 0)
    {
        SDL_Surface *screen = NULL;
        Color pixel;
        int width = WIDTH;
        int height = HEIGHT;

        Logger::log(LOG_INFO)<<"Starting client in standalone mode"<<endl;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            Logger::log(LOG_ERROR)<<"Problem during SDL initialisation: "<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

        Logger::log(LOG_INFO)<<"SDL initialised"<<endl;

        const SDL_VideoInfo* videoInfos = SDL_GetVideoInfo();

        if (0.9*videoInfos->current_w < WIDTH) { // the screen is too small for the predifined resolution
            width = 0.9*videoInfos->current_w;
            height = width * HEIGHT / WIDTH; // to keep the screen ratio
        }

        screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

        // scene loading
        TestScenes testScenes;
        Scene scene = testScenes.createTestScene1(width, height);

        if (screen == NULL)
        {
            Logger::log(LOG_ERROR)<<"Problem during screen initialisation: "<<SDL_GetError()<<endl;
            exit(EXIT_FAILURE);
        }

        SDL_WM_SetCaption("PRay rendering", NULL);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        Logger::log(LOG_INFO)<<"Screen initialised"<<endl;

        Logger::log(LOG_INFO)<<"Rendering started"<<endl;

        SDL_Event event;
        bool rendering = true;

        while ( rendering )
        {
            std::cout << "camera.point = " << scene.getCamera()->getPoint().x << " , "
                                           << scene.getCamera()->getPoint().y << " , "
                                           << scene.getCamera()->getPoint().z << endl;

            for (int y=0 ; y < height ; y++)
            {
                for (int x=0 ; x < width ; x++)
                {
                    pixel = scene.renderPixel(x,y);

                    pixelRGBA(screen, x, y, pixel.getR(), pixel.getG(), pixel.getB(), 255);
                }
            }

            SDL_Flip(screen);

            bool waiting = true;

            while (waiting)
            {
                waiting = false;

                SDL_WaitEvent(&event);

                switch (event.type)
                {
                case SDL_QUIT:
                    rendering = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_ESCAPE:
                        rendering = false;
                        break;
                    case SDLK_UP:
                        scene.getCamera()->setPoint(Vec4<float>(scene.getCamera()->getPoint().x + 5,
                                                                scene.getCamera()->getPoint().y,
                                                                scene.getCamera()->getPoint().z));
                        break;
                    case SDLK_DOWN:
                        scene.getCamera()->setPoint(Vec4<float>(scene.getCamera()->getPoint().x - 5,
                                                                scene.getCamera()->getPoint().y,
                                                                scene.getCamera()->getPoint().z));
                        break;
                    case SDLK_LEFT:
                        scene.getCamera()->setPoint(Vec4<float>(scene.getCamera()->getPoint().x,
                                                                scene.getCamera()->getPoint().y + 5,
                                                                scene.getCamera()->getPoint().z));
                        break;
                    case SDLK_RIGHT:
                        scene.getCamera()->setPoint(Vec4<float>(scene.getCamera()->getPoint().x,
                                                                scene.getCamera()->getPoint().y - 5,
                                                                scene.getCamera()->getPoint().z));
                        break;
                    default:
                        waiting = true;
                        break;
                    }
                    break;
                default:
                    waiting = true;
                    break;
                }
            }
        }

        Logger::log(LOG_INFO)<<"Rendering complete"<<endl;

        SDL_SaveBMP(screen, "image.bmp");

        Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

        testScenes.destroyTestScene1(scene);
        SDL_FreeSurface(screen);
        SDL_Quit();

    }

    return EXIT_SUCCESS;
}
