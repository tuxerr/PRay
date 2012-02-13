#ifndef DEF_DISPLAY
#define DEF_DISPLAY

#define DEFAULT_HEIGHT 1280
#define DEFAULT_WIDTH 720
#define DEFAULT_FULLSCREEN false
#define DEFAULT_NAME "PRay Renderer"

#include "logger.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <SDL/SDL.h>
#include <SDL/SDL_version.h>
#include "color.hpp"
#include <algorithm>


using namespace std;

class Display {
public:
    static void init(int height=DEFAULT_HEIGHT,int width=DEFAULT_WIDTH);
    static Display& getInstance();
#ifndef __INTEL_COMPILER
    void register_keyhook(std::function<void(void)> met,SDLKey key);
#endif
    void refresh_display();
    bool refresh_controls();
    bool new_control_press();
    bool quit();
    int get_width();
    int get_height();
    void add_pixel(int width,int height,Color color);
    void add_surface(int x,int y,int width,int height,std::vector<Color> &pixels);

private:
    Display(int height,int width); // constructeur en privé, classe singleton
    Display(Display const&);    // pas d'implémentation, mais force le singleton
    void operator=(Display const&);  // pas d'implémentation, mais force le singleton
    ~Display();
    int height;
    int width;
    static Display *display_ptr;
    bool quit_pressed;
#ifndef __INTEL_COMPILER
    std::vector< std::pair< std::function<void(void)>,SDLKey > > bindings;
#endif
    SDL_Surface *screen;
    bool new_press;
};

#endif
