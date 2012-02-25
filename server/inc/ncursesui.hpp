#ifndef DEF_NCURSESUI
#define DEF_NCURSESUI

#include <iostream>
#include <ncurses.h>
#include <functional>
#include <string>
#include "logger.hpp"
#include "settings.hpp"
#include <queue>
#include <map>

class NetworkRenderer;

using namespace std;

typedef enum {
    STRING_NORMAL,
    STRING_RED,
    STRING_GREEN
} String_Properties;

typedef struct {
    std::string text;
    String_Properties prop;
} String_Entry;

class NcursesScrollingWindow {
public:
    NcursesScrollingWindow(string title,int height,int width,int starty,int startx,int scroll_up,int scroll_down);
    ~NcursesScrollingWindow();
    int add_string(string text);
    string get_string(int id);
    void modify_string(int id,string new_text);
    void set_string_property(int id,String_Properties prop);
    void remove_string(int id);
    void refresh(int enter_char);
    
private:    
    WINDOW *ptr;
    std::map<int,String_Entry> messages;
    unsigned int line_size;
    unsigned int col_size;
    int scroll_up_char;
    int scroll_down_char;
    int first_string;
    int act_id;
  
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
    unsigned int line_size;
    unsigned int col_size;
};

class NcursesTextWindow {
public:
    NcursesTextWindow(int width,int starty,int startx);
    ~NcursesTextWindow();
    string get_current_string();
    void refresh(int mode_ch);
private:
    string current_string;
    WINDOW *ptr;
    unsigned int col_size;
};

class NcursesUI {
public :
    NcursesUI();
    ~NcursesUI();
    void init();
    void run(NetworkRenderer &renderer);
    NcursesScrollingWindow* get_clients_win();
    NcursesLogWindow* get_log_win();
    NcursesLogWindow* get_status_win();

private :
    int mode_ch;
    NcursesScrollingWindow *client_ptr;
    NcursesLogWindow *log_ptr;
    NcursesLogWindow *status_ptr;
    NcursesTextWindow *text_ptr;
};

#endif
