#ifndef DEF_DISPLAY
#define DEF_DISPLAY

#define DEFAULT_HEIGHT 1280
#define DEFAULT_WIDTH 720
#define DEFAULT_FULLSCREEN false
#define DEFAULT_NAME "PRay Renderer"

#include "logger.h"
#include <vector>
#include <map>
#include "method.h"
#include <SDL/SDL.h>
#include "color.h"

class Display {
public:
    static void init(int height=DEFAULT_HEIGHT,int width=DEFAULT_WIDTH);
    static Display& getInstance();
    void register_keyhook(Method<void> met,SDLKey key);
    void refresh_display();
    void refresh_controls();
    bool quit();
    void add_pixel(Color color,int width,int height);

private:
    Display(int height,int width); // constructeur en privé, classe singleton
    Display(Display const&);    // pas d'implémentation, mais force le singleton
    void operator=(Display const&);  // pas d'implémentation, mais force le singleton
    ~Display();
    int height;
    int width;
    static Display *display_ptr;
    bool quit_pressed;
    std::map<Method<void>,SDLKey> bindings;
    SDL_Surface *screen;
};

#endif
