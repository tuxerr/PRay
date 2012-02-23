#include "ncursesui.hpp"

NcursesUI::NcursesUI() : 
    client_ptr(NULL), log_ptr(NULL), status_ptr(NULL)
{
}

NcursesUI::~NcursesUI()
{
    endwin(); // end curses mode
    Logger::getInstance().use_stdout_output();
    delete client_ptr;
    delete log_ptr;
    delete status_ptr;
}


void NcursesUI::init()
{
    initscr(); // start curses mode
    cbreak(); // line buffering disabled
    keypad(stdscr, TRUE); // reading keys like F1, F2, arrows keys

    Logger::log()<<"Starting ncurses server UI"<<std::endl;

    refresh();
    client_ptr=new NcursesScrollingWindow("Clients",LINES-1,COLS/3,0,COLS/3,KEY_UP,KEY_DOWN);
    log_ptr=new NcursesLogWindow("Logs",LINES-1,COLS/3,0,COLS*2/3);
    status_ptr=new NcursesLogWindow("Status",LINES-1,COLS/3,0,0);
    Logger::getInstance().redirect_output(std::bind(&NcursesLogWindow::add_string,log_ptr,std::placeholders::_1));
    Logger::log()<<"Ncurses Init"<<std::endl;
}

NcursesScrollingWindow* NcursesUI::get_clients_win() {
    return client_ptr;
}

NcursesLogWindow* NcursesUI::get_log_win() {
    return log_ptr;
}

NcursesLogWindow* NcursesUI::get_status_win() {
    return status_ptr;
}

void NcursesUI::run()
{
    string current_input;
    // 27 is the ESCAPE key
    while (mode_ch != 27 && mode_ch != KEY_EXIT)
    {
        mode_ch = getch();

        (*client_ptr).refresh(mode_ch);

        wmove(stdscr,LINES-1,current_input.size()+0);

        if(mode_ch==KEY_BACKSPACE) {
            current_input=current_input.substr(0,current_input.length()-1);
        } else if(mode_ch==KEY_BREAK) {
            stringstream input_ss(stringstream::out | stringstream::in);
            input_ss<<current_input;
            
            string head="";
            input_ss>>head;
            if(head=="scene") {

            } else if(head=="render") {

            }

            current_input="";
        } else if(mode_ch!=-1) {
            current_input.push_back((char)mode_ch);
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
    refresh();
}

void NcursesLogWindow::refresh() {
    int col=1;
    for(std::deque<std::string>::iterator it = messages.begin();it!=messages.end();it++) {

        string cutstr = (*it).substr(0,col_size);
        string newstr = cutstr.append(col_size-cutstr.length(),' ');
        
        mvwprintw(ptr,col,1,newstr.c_str());
        col++;
    }
    wrefresh(ptr);
}

NcursesScrollingWindow::NcursesScrollingWindow(string title,int height,int width,int starty,int startx,int scroll_up,int scroll_down) : 
    scroll_up_char(scroll_up), scroll_down_char(scroll_down), 
    first_string(0), act_id(0)
{
    ptr = newwin(height,width,starty,startx);
    box(ptr,0,0);
    mvwprintw(ptr,0,(width-title.size())/2,title.c_str());
    line_size=height-2;
    col_size=width-2;
    refresh(-1);
}

NcursesScrollingWindow::~NcursesScrollingWindow() {
    delwin(ptr);
}

int NcursesScrollingWindow::add_string(string text) {
    String_Entry ent;
    ent.text=text;
    ent.prop=STRING_NORMAL;
    messages[act_id]=ent;
    act_id++;
    return act_id;
}

string NcursesScrollingWindow::get_string(int id) {
    if(messages.find(id)==messages.end()) {
        return "";
    } else {
        return messages[id].text;
    }
}

void NcursesScrollingWindow::modify_string(int id,string new_text) {
    if(messages.find(id)!=messages.end()) {
        messages[id].text=new_text;
    }
    refresh(-1);
}

void NcursesScrollingWindow::remove_string(int id) {
    messages.erase(id);
    refresh(-1);
}

void NcursesScrollingWindow::set_string_property(int id,String_Properties prop) {
    if(messages.find(id)!=messages.end()) {
        messages[id].prop=prop;
    }
    refresh(-1);
}

void NcursesScrollingWindow::refresh(int enter_char) {
    if(enter_char==scroll_up_char) {
        if(first_string>0)
            first_string--;
    } else if(enter_char==scroll_down_char) {
        if(first_string+line_size<messages.size()) {
            first_string++;
        }
    }

    int col=1;
    int iter_act=0;
    for(std::map<int,String_Entry>::iterator it = messages.begin() ; it!=messages.end();it++) {
        if(iter_act>=first_string && iter_act<first_string+(int)line_size) {
            string newstr = (*it).second.text.append(col_size-(*it).second.text.size(),' ');
        
            mvwprintw(ptr,col,1,newstr.c_str());
            col++;
        }
        iter_act++;
    }
    wrefresh(ptr);

}

