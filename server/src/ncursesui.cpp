#include "ncursesui.h"

NcursesUI::NcursesUI() :
    preview_ping(0),
    mode(m_start)
{
}

NcursesUI::~NcursesUI()
{
    endwin(); // end curses mode
}


void NcursesUI::init()
{
    initscr(); // start curses mode
    clear();
    cbreak(); // line buffering disabled
    keypad(stdscr, TRUE); // reading keys like F1, F2, arrows keys
    noecho(); // no echo() while getch()
    getmaxyx(stdscr,row,col);
    Logger::log()<<"Starting ncurses server UI"<<endl;
}

void NcursesUI::run()
{
    while (mode != m_quit)
    {
        clear();

        switch (mode)
        {
        case m_start:
            prev_mode = mode;
            attron(A_BOLD);
            mvprintw(2,2,"Welcome");
            attroff(A_BOLD);
            mvprintw(5,5,"c -> command");
            mvprintw(6,5,"l -> log");
            mvprintw(7,5,"p -> ping");
            mvprintw(8,5,"q -> quit");
            move(row-1,col-1);
            break; 
        case m_command:
            nocbreak();
            echo();
            mvprintw(2,2,"Command mode");
            mvprintw(3,2,">");
            move(3,4);
            getstr(command);
            mvprintw(10,3,"Execution of ...");
            mvprintw(11,3,"%s", command);
            mode = prev_mode;
            break;
        case m_log:
            prev_mode = mode;
            mvprintw(2,2,"Log mode");
            for (int i=4 ; i < row-2 ; i++)
                mvprintw(i,3,"[%2d] Message", i-3);
            move(row-1,col-1);
            Logger::log()<<"in Log mode"<<endl;
            break;

        case m_ping:
            prev_mode = mode;
            mvprintw(2,2,"Ping mode");
            mvprintw(5,2,"Client : %d ms", preview_ping++);
            move(row-1,col-1);
            break;
        default:
            break;
        }

        refresh();
        
        halfdelay(10);

        mode_ch = getch();

        switch (mode_ch) {
        case 'c':
            mode = m_command;
            break;
        case 'l':
            mode = m_log;
            break;
        case 'p':
            mode = m_ping;
            break;
        case 'q':
            mode = m_quit;
            break;
        default:
            break;
        }

        mode_ch = 0;
    }
}
