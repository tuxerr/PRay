#include "display.h"

void Display::init(int height,int width) {
    static Display disp(height,width);
    display_ptr=&disp;
}

Display& Display::getInstance() {
    return *display_ptr;
}

void Display::register_keyhook(Method<void> met,SDLKey key) {
    map.add(met,key);
}

void Display::refresh_display() {
    SDL_Flip(screen);
}

void Display::refresh_controls() {
    SDL_Event event;
    bool keydown=true;
    while(SDL_PollEvent(&event)==1) {

        switch(event.type) {
        case SDL_KEYDOWN:
            std::map<SDLKey, Method<void> >::iterator it = map.find(event.key.keysym.sym);
            if(it!=map.end()) {
                it->first.call();
            }
            break;

        case SDL_QUIT:
            quit_pressed=true;
            break;

        default:
            break;
        }

    }
}

bool Display::quit() {
    return quit_pressed;
}

Display::Display(int width,int height) : 
    height(height),width(width), quit_pressed(false), screen(null)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Logger::log(LOG_ERROR)<<"Problem during SDL initialisation: "<<SDL_GetError()<<endl;
        exit(EXIT_FAILURE);
    }

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    const SDL_VideoInfo* videoInfos = SDL_GetVideoInfo();

    if (0.9*videoInfos->current_w < WIDTH) { // the screen is too small for the predifined resolution
        width = 0.9*videoInfos->current_w;
        height = width * HEIGHT / WIDTH; // to keep the screen ratio
    }

    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    Logger::log(LOG_INFO)<<"SDL initialised (video and controls)"<<endl;
}

Display::~Display() {
    SDL_Quit();
    Logger::log(LOG_INFO)<<"SDL Quit"<<endl;
}

void Display::add_pixel(int x,int y,Color color) {
    // all pixels are 32b-encoded
    Uint32 *p = (Uint32 *)screen->pixels + x * 4 + y * screen->pitch;
    *p=SDL_MapRGB(screen->format,color.getR(),color.getG(),color.getB());
}

void Display::add_surface(int x,int y,int width,int height,std::vector<Color> &pixels) {
    // all pixels are 32b-encoded
    int i=0;
    for(int h=0;h<height;h++) {
        for(int w=0;w<width;w++) {
            Uint32 *p = (Uint32 *)screen->pixels + (x+w) * 4 + (y+h) * screen->pitch;
            *p=SDL_MapRGB(screen->format,pixels[i].getR(),pixels[i].getG(),pixels[i].getB());
            i++;
        }        
    }
}
