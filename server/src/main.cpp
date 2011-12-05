#include <ncurses.h>

using namespace std;

int main(int argv, char *argc[])
{
    initscr(); // start curses mode
    clear();
    cbreak(); // line buffering disabled
    keypad(stdscr, TRUE); // reading keys like F1, F2, arrows keys
    noecho(); // no echo() while getch()

    enum mode_e { 
        m_start,
        m_command,
        m_log, 
        m_ping, 
        m_quit
    };
    
    int row,col;
    int mode_ch;
    enum mode_e mode = m_start;

    getmaxyx(stdscr,row,col);

    while (mode != m_quit)
    {
        clear();

        switch (mode)
        {
        case m_start:
            attron(A_BOLD);
            printw("Welcome\n");
            attroff(A_BOLD);
            mvprintw(5,5,"c -> command\n");
            mvprintw(6,5,"l -> log\n");
            mvprintw(7,5,"p -> ping\n");
            mvprintw(8,5,"q -> quit\n");
            break;
        case m_command:
            printw("Command mode\n");
            printw("> ");
            break;
        case m_log:
            printw("Log mode\n");
            break;
        case m_ping:
            printw("Ping mode\n");
            break;
        default:
            break;
        }

        move(row-1,col-1);

        refresh();

        mode_ch = getch(); // halfdelay()

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
    }
    
    endwin(); // end curses mode

    return 0;
}
