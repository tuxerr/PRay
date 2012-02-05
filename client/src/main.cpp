#include <cstdlib>
#include <string>
#include <SDL/SDL_gfxPrimitives.h>
#include "logger.h"
#include "server.h"
#include "color.h"
#include "testScenes.h"

#define WIDTH  1280
#define HEIGHT  720

#define CAM_TRANS_FACTOR  5
#define CAM_ROT_ANGLE     2

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
	  /*
            Logger::log(LOG_DEBUG) << "Camera point=("
                                   << scene.getCamera()->getPoint().x << ","
                                   << scene.getCamera()->getPoint().y << ","
                                   << scene.getCamera()->getPoint().z 
				   << ") direction=("
				   << scene.getCamera()->getDirection().x << ","
				   << scene.getCamera()->getDirection().y << ","
				   << scene.getCamera()->getDirection().z
				   << ") normal=("
				   << scene.getCamera()->getNormal().x << ","
				   << scene.getCamera()->getNormal().y << ","
				   << scene.getCamera()->getNormal().z << ")" << endl;
	  */

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
                            cam->setPoint(cam->getPoint() + cam->getDirection()*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_s:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - cam->getDirection()*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_q:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - cam->getDirection().cross(cam->getNormal())*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_d:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() + cam->getDirection().cross(cam->getNormal())*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_a:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() - Vec3<float>(0,0,1)*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_e:
                        {
                            Camera* cam = scene.getCamera();
                            cam->setPoint(cam->getPoint() + Vec3<float>(0,0,1)*CAM_TRANS_FACTOR);
                        }
                        break;
                    case SDLK_LEFT:
                        {
                            Camera* cam = scene.getCamera();
                            Vec3<float> axis = Vec3<float>(0,0,1);
                            cam->setDirection(cam->getDirection().rotate(-CAM_ROT_ANGLE, axis));
                            cam->setNormal(cam->getNormal().rotate(-CAM_ROT_ANGLE, axis));
                        }
                        break;
                    case SDLK_RIGHT:
                        {
                            Camera* cam = scene.getCamera();
                            Vec3<float> axis = Vec3<float>(0,0,1);
                            cam->setDirection(cam->getDirection().rotate(CAM_ROT_ANGLE, axis));
                            cam->setNormal(cam->getNormal().rotate(CAM_ROT_ANGLE, axis));
                        }
                        break;
                    case SDLK_UP:
                        {
                            Camera* cam = scene.getCamera();
                            Vec3<float> axis = cam->getDirection().cross(cam->getNormal());
                            cam->setDirection(cam->getDirection().rotate(CAM_ROT_ANGLE, axis));
                            cam->setNormal(cam->getNormal().rotate(CAM_ROT_ANGLE, axis));
                        }
                        break;
                    case SDLK_DOWN:
                        {
                            Camera* cam = scene.getCamera();
                            Vec3<float> axis = cam->getDirection().cross(cam->getNormal());
                            cam->setDirection(cam->getDirection().rotate(-CAM_ROT_ANGLE, axis));
                            cam->setNormal(cam->getNormal().rotate(-CAM_ROT_ANGLE, axis));
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
