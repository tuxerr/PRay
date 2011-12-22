#include <cstdlib>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "logger.h"
#include "color.h"
#include "testScenes.h"

#define WIDTH  1280/3
#define HEIGHT  720/3


int main()
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
            Logger::log(LOG_DEBUG) << "camera.point = "
                                   << scene.getCamera()->getPoint().x << " , "
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
                case SDL_KEYDOWN: // see the README for keys
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_ESCAPE:
                        rendering = false;
                        break;
                    case SDLK_z:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() + cam->getDirection());
                        }
                        break;
                    case SDLK_s:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - cam->getDirection());
                        }
                        break;
                    case SDLK_q:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - cam->getDirection().cross(cam->getNormal()));
                        }
                        break;
                    case SDLK_d:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() + cam->getDirection().cross(cam->getNormal()));
                        }
                        break;
                    case SDLK_a:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - Vec4<float>(0,0,1));
                        }
                        break;
                    case SDLK_e:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() + Vec4<float>(0,0,1));
                        }
                        break;
                    case SDLK_LEFT:
                        {
                            Camera* cam = scene.getCamera();
                            Vec4<float> axis = Vec4<float>(0,0,1);
                            cam->setDirection(cam->getDirection().rotate(1, axis));
                            cam->setNormal(cam->getNormal().rotate(1, axis));
                        }
                        break;
                    case SDLK_RIGHT:
                        {
                            Camera* cam = scene.getCamera();
                            Vec4<float> axis = Vec4<float>(0,0,1);
                            cam->setDirection(cam->getDirection().rotate(-1, axis));
                            cam->setNormal(cam->getNormal().rotate(-1, axis));
                        }
                        break;
                    case SDLK_UP:
                        {
                            Camera* cam = scene.getCamera();
                            Vec4<float> axis = cam->getDirection().cross(cam->getNormal());
                            cam->setDirection(cam->getDirection().rotate(1, axis));
                            cam->setNormal(cam->getNormal().rotate(1, axis));
                        }
                        break;
                    case SDLK_DOWN:
                        {
                            Camera* cam = scene.getCamera();
                            Vec4<float> axis = cam->getDirection().cross(cam->getNormal());
                            cam->setDirection(cam->getDirection().rotate(-1, axis));
                            cam->setNormal(cam->getNormal().rotate(-1, axis));
                        }
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
