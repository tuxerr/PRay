#include <ncurses.h>

using namespace std;

int main(int argv, char *argv[])
{
    initscr(); // start curses mode
    cbreak(); // line buffering disabled
    keypad(stdscr, TRUE); // reading keys like F1, F2, arrows keys
    noecho(); // no echo() while getch()

    refresh();
    
    endwin(); // end curses mode

    return 0;
}
