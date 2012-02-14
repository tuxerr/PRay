#ifndef DEF_NCURSESUI
#define DEF_NCURSESUI

#include <iostream>
#include <ncurses.h>
#include <functional>
#include <string>
#include "logger.hpp"
#include <queue>

using namespace std;

class NcursesUI {
public :
    NcursesUI();
    ~NcursesUI();
    void init();
    void run();

private :
    int mode_ch;
};

class NcursesLogWindow {
public:
    NcursesLogWindow(string title,int height,int width,int starty,int startx);
    ~NcursesLogWindow();
    void add_string(string text);
    void refresh();

private:
    WINDOW *ptr;
    std::deque<std::string> messages;
    unsigned int max_size;
    unsigned int col_size;
};

class NcursesTextWindow {
    
};

#endif
