#include "display.hpp"

Display* Display::display_ptr;

void Display::init(int height,int width) {
    static Display disp(height,width);
    display_ptr=&disp;

}

Display& Display::getInstance() {
    return *display_ptr;
}

#ifndef __INTEL_COMPILER
void Display::register_keyhook(std::function< void(void) > met,SDLKey key) {
    bindings.push_back(pair<std::function<void(void)>,SDLKey>(met,key));
}
#endif

void Display::refresh_display() {
    if(line_refresh) {
        SDL_UpdateRect(screen,0,0,0,0);
        last_refresh=SDL_GetTicks();
    } else {
        Logger::log()<<"Flipping"<<std::endl;
        SDL_UpdateRect(screen,0,0,0,0);
//        SDL_Flip(screen);
    }

}

void Display::refresh_part_display_timecheck() {
    if(line_refresh) {
        if(SDL_GetTicks()-last_refresh>MINIMUM_TIMECHECK_REFRESH_TIME) {
            for (std::set<int>::iterator it=new_lines_to_refresh.begin();
                 it!=new_lines_to_refresh.end();
                 it++) {
                SDL_UpdateRect(screen,0,*it,width,1);
            }
            last_refresh=SDL_GetTicks();
            new_lines_to_refresh.clear();
        }
    }
}

bool Display::refresh_controls() {
    SDL_Event event;
    bool change=false;
    while(SDL_PollEvent(&event)==1) {
        switch(event.type) {
        case SDL_KEYDOWN:
#ifndef __INTEL_COMPILER
            for(unsigned int i=0;i<bindings.size();i++) {
                if(bindings[i].second == event.key.keysym.sym) {
                    (bindings[i].first)();
                    change=true;
                    new_press=true;
                }
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    quit_pressed=true;
                }
            }
#endif
            break;

        case SDL_QUIT:
            quit_pressed=true;
            break;

        default:
            break;
        }
    }

    return change;
}

bool Display::new_control_press() {
    if(new_press) {
        new_press=false;
        return true;
    } else {
        return new_press;
    }
}

bool Display::quit() {
    return quit_pressed;
}

Display::Display(int p_width,int p_height) :
    height(p_height),width(p_width), quit_pressed(false), screen(NULL), new_press(true), last_refresh(0)
{

    line_refresh=Settings::getAsBool("line_refresh");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Logger::log(LOG_ERROR)<<"Problem during SDL initialisation: "<<SDL_GetError()<<endl;
        exit(EXIT_FAILURE);
    }

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    const SDL_VideoInfo* videoInfos = SDL_GetVideoInfo();

    if (videoInfos->current_w < width) { // the screen is too small for the predifined resolution
        width = 0.9*videoInfos->current_w;
        height = 0.9*videoInfos->current_h; // to keep the screen ratio
    }

    SDL_WM_SetCaption(DEFAULT_NAME,NULL);

    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    Logger::log(LOG_INFO)<<"SDL initialised (video and controls) in "<<width<<"x"<<height<<endl;
}

Display::~Display() {
    SDL_SaveBMP(screen, "image.bmp");
    Logger::log(LOG_INFO)<<"Rendered image saved"<<endl;

    SDL_FreeSurface(screen);
    SDL_Quit();
    Logger::log(LOG_INFO)<<"SDL Quit"<<endl;
}

int Display::get_width() {
    return width;
}

int Display::get_height() {
    return height;
}

void Display::add_pixel(int x,int y,Color color) {
    // all pixels are 32b-encoded
    SDL_LockSurface(screen);
    Uint32 *p = (Uint32 *)screen->pixels + x  + y * screen->pitch/4;
    *p=SDL_MapRGB(screen->format,color.getR()*255,color.getG()*255,color.getB()*255);
//  Logger::log()<<"Updating pixel "<<x<<y<<std::endl;
    new_lines_to_refresh.insert(y);
    SDL_UnlockSurface(screen);
}

void Display::add_surface(int x,int y,int width,int height,std::vector<Color> &pixels) {
    Logger::log()<<x<<"/"<<y<<"/"<<width<<"/"<<height<<std::endl;
    SDL_LockSurface(screen);
    // all pixels are 32b-encoded
    int i=0;
    for(int h=0;h<height;h++) {
        for(int w=0;w<width;w++) {
            Uint32 *p = (Uint32 *)screen->pixels + (x+w) + (y+h) * (screen->pitch/4);
            *p=SDL_MapRGB(screen->format,pixels[i].getR()*255,pixels[i].getG()*255,pixels[i].getB()*255);
            i++;
        }
        new_lines_to_refresh.insert(y+h);
    }
    SDL_UnlockSurface(screen);
}

void Display::add_line_group(int x,int y,std::vector<Color> &pixels) {
    // all pixels are 32b-encoded
    // adds to the display texture a group of lined pixels that can go from line to line (end/beginning)
    SDL_LockSurface(screen);
    int currentx=x;
    int currenty=y;
    new_lines_to_refresh.insert(currenty);
    for(unsigned int i=0;i<pixels.size();i++) {
        Uint32 *p = (Uint32 *)screen->pixels + currentx  + currenty * screen->pitch/4;
        *p=SDL_MapRGB(screen->format,pixels[i].getR()*255,pixels[i].getG()*255,pixels[i].getB()*255);
        if(currentx<width-1) {
            currentx++;
        } else {
            currentx=0;
            currenty++;
            new_lines_to_refresh.insert(currenty);
        }
    }
    SDL_UnlockSurface(screen);

}
