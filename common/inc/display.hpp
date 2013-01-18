#ifndef DEF_DISPLAY
#define DEF_DISPLAY

#define DEFAULT_HEIGHT 1280
#define DEFAULT_WIDTH 720
#define DEFAULT_NAME "PRay Renderer"
#define MINIMUM_TIMECHECK_REFRESH_TIME 30

#include "logger.hpp"
#include "settings.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <SDL/SDL.h>
#include <SDL/SDL_version.h>
#include "color.hpp"
#include <algorithm>
#include <set>

using namespace std;

class Display {
public:
    static void init(int height=DEFAULT_HEIGHT,int width=DEFAULT_WIDTH);
    static Display& getInstance();
    void register_keyhook(std::function<void(void)> met,SDLKey key);
    void refresh_display();
    void refresh_part_display_timecheck();
    bool refresh_controls();
    bool new_control_press();
    bool quit();
    int get_width();
    int get_height();
    void add_pixel(int width,int height,Color color);
    void add_surface(int x,int y,int width,int height,std::vector<Color> &pixels);
    void add_line_group(int x,int y,std::vector<Color> &pixels);

private:
    Display(int height,int width); // constructeur en privé, classe singleton
    Display(Display const&);    // pas d'implémentation, mais force le singleton
    void operator=(Display const&);  // pas d'implémentation, mais force le singleton
    ~Display();
    int height;
    int width;
    static Display *display_ptr;
    bool quit_pressed;
    std::vector< std::pair< std::function<void(void)>,SDLKey > > bindings;
    SDL_Surface *screen;
    bool new_press;
    Uint32 last_refresh;
    std::set<int> new_lines_to_refresh;
    bool line_refresh;
};

#endif
