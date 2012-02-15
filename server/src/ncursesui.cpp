#include "ncursesui.hpp"

NcursesUI::NcursesUI()
{
}

NcursesUI::~NcursesUI()
{
    endwin(); // end curses mode
}


void NcursesUI::init()
{
    initscr(); // start curses mode
    cbreak(); // line buffering disabled
    keypad(stdscr, TRUE); // reading keys like F1, F2, arrows keys
    noecho(); // no echo() while getch()

    Logger::log()<<"Starting ncurses server UI"<<std::endl;

    refresh();
}

void NcursesUI::run()
{
    NcursesLogWindow log_win("Logs",LINES-1,COLS/3,0,COLS*2/3);
    NcursesLogWindow clients_win("Clients",LINES-1,COLS/3,0,COLS/3);
    NcursesLogWindow status_win("Status",LINES-1,COLS/3,0,0);

    while (mode_ch != 'q')
    {
//        refresh();
        
        halfdelay(5);

        mode_ch = getch();
        if(mode_ch=='a') {
            log_win.add_string("trolol");
            log_win.refresh();
        }

        if(mode_ch=='z') {
            log_win.add_string("trolol2");
            log_win.refresh();
        }

    }
}

NcursesLogWindow::NcursesLogWindow(string title,int height,int width,int starty,int startx) {
    ptr = newwin(height,width,starty,startx);
    box(ptr,0,0);
    mvwprintw(ptr,0,(width-title.size())/2,title.c_str());
    line_size=height-2;
    col_size=width-2;
    refresh();
}

NcursesLogWindow::~NcursesLogWindow() {
    delwin(ptr);
}

void NcursesLogWindow::add_string(string text) {
    if(messages.size()>=line_size) {
        messages.pop_front();
    }
    messages.push_back(text);
}

void NcursesLogWindow::refresh() {
    int col=1;
    for(std::deque<std::string>::iterator it = messages.begin();it!=messages.end();it++) {
        string newstr = (*it).append(col_size-(*it).size(),' ');
        
        mvwprintw(ptr,col,1,newstr.c_str());
        col++;
    }
    wrefresh(ptr);
}

NcursesScrollingWindow::NcursesScrollingWindow(string title,int height,int width,int starty,int startx,int scroll_up,int scroll_down) : 
    scroll_up_char(scroll_up), scroll_down_char(scroll_down), first_string(0)
{
    ptr = newwin(height,width,starty,startx);
    box(ptr,0,0);
    mvwprintw(ptr,0,(width-title.size())/2,title.c_str());
    line_size=height-2;
    col_size=width-2;
    refresh();
}

NcursesScrollingWindow::~NcursesScrollingWindow() {
    delwin(ptr);
}

int NcursesScrollWindow::add_string(string text) {
    
}

void NcursesScrollWindow::remove_string(int id) {
    messages.erase(id);
    refresh(-1);
}

void NcursesScrollWindow::refresh(int enter_char) {
    if(enter_char==scroll_up_char) {
        if(first_string>0)
            first_string--;
    } else if(enter_char==scroll_down_char) {
        if(first_string+line_size<messages.size()) {
            first_string++;
        }
    }

    int col=1;
    for(std::map<std::string>::iterator it = messages.begin();it!=messages.end();it++) {
        string newstr = (*it).second.append(col_size-(*it).second.size(),' ');
        
        mvwprintw(ptr,col,1,newstr.c_str());
        col++;
    }
    wrefresh(ptr);

}

