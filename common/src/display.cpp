#include "display.h"

Display::init(int height,int width) {
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
            std::map<Method<void>,SDLKey>::iterator it = map.find(event.key.keysym.sym);
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

bool Display::escape_pressed() {
    return esc_pressed;
}

Display::Display(int width,int height) : 
    height(height),width(width), quit_pressed(false), screen(null)
{
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
}

Display::~Display() {
    SDL_Quit();
    Logger::log(LOG_INFO)<<"SDL Quit"<<endl;
}
