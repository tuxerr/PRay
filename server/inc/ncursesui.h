#ifndef DEF_NCURSESUI
#define DEF_NCURSESUI

#include <iostream>
#include <ncurses.h>
#include <functional>
#include <string>
#include <string.h>
#include "logger.h"
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

class NcursesWindow {
public:
    NcursesWindow(string title,int height,int width,int starty,int startx);
    ~NcursesWindow();
    void add_string(string text);
    void refresh();

private:
    WINDOW *ptr;
    std::deque<std::string> messages;
    unsigned int max_size;
    unsigned int col_size;
};

#endif
