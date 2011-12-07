#ifndef DEF_NCURSESUI
#define DEF_NCURSESUI

#include "logger.h"

enum mode_e { 
    m_start,
    m_command,
    m_log, 
    m_ping, 
    m_quit
};

class NcursesUI {
private :
    Logger log;
    int preview_ping;
    char command[256];
    int row;
    int col;
    int mode_ch;
    enum mode_e mode;
    enum mode_e prev_mode;
public :
    NcursesUI(Logger);
    ~NcursesUI();
    void init();
    void run();
};

#endif
