#include "logger.hpp"

using namespace std;

Logger* Logger::logger_ptr;

void (*Logger::sigsegv_handlerptr)(int);

LoggerStreambuf::LoggerStreambuf(string &prefix,fstream &file,Mutex &mut) :
    prefix(prefix), file(file), write_mut(mut), cout_output(true), fun_output(false), firstflush(true)

{
    setp (buffer, buffer+(bufferSize-1));
}

void LoggerStreambuf::set_redirection_ptr(std::function<void(string)> fun) {
    redirection=fun;
}

void LoggerStreambuf::use_cout_output(bool use) {
    cout_output=use;
}

void LoggerStreambuf::use_fun_output(bool use) {
    fun_output=use;
}

int LoggerStreambuf::flushBuffer () {
    int num = pptr()-pbase();
    if(firstflush && num!=0) {
        file<<prefix;
        if(cout_output) {
            std::cout<<prefix;
        }
        if(fun_output) {
            current_log.append(prefix);
        }
        firstflush=false;
    }
    if(num!=0) {
        file.write(buffer,num);
        if(cout_output) {
            std::cout.write(buffer,num);
        } 
        if(fun_output) {
            string res(buffer,num-1);
            current_log.append(res);
        }
        pbump(-num); // reset put pointer accordingly
    }
    return num;
}

int LoggerStreambuf::overflow ( int c ) {
    if (c != EOF) {
        *pptr() = c;    // insert character into the buffer
        pbump(1);
    }
    if (flushBuffer() == EOF)
        return EOF;
    return c;
}

int LoggerStreambuf::sync() {
    if (flushBuffer() == EOF)
        return -1;    // ERROR
    firstflush=true;
    if(fun_output) {
        redirection(current_log);
        current_log="";
    }

    write_mut.unlock();

    return 0;
}

void Logger::init(string file_path) {
    static Logger log(file_path);
    logger_ptr=&log;
    Logger::sigsegv_handlerptr=signal(SIGSEGV,Logger::sigsegv_newhandler);
}

void Logger::sigsegv_newhandler(int sig) {
    Logger::log(LOG_ERROR)<<"Segmentation Fault"<<std::endl;
    Logger::log().close();
    (*Logger::sigsegv_handlerptr)(sig);
}

Logger& Logger::log(Log_Type type) {
    if(logger_ptr!=NULL) {

	logger_ptr->set_logtype(type);
        return *logger_ptr;
    } else {
        cerr<<"Logger class is not initiated"<<endl;
        exit(0);
    }
}

Logger& Logger::getInstance() {
    if(logger_ptr!=NULL) {
        return *logger_ptr;
    } else {
        cerr<<"Logger class is not initiated"<<endl;
        exit(0);
    }
}

void Logger::close() {
    if(m_file) {
        m_file.close();
    }
}

Logger::Logger(string file_path) :
    ios(0), ostream(new LoggerStreambuf(current_prefix,m_file,write_mut)), current_prefix("[INF]")
{
    m_file.open(file_path.c_str(),ios::out|ios::trunc);
    if(!m_file) {
        cerr<<"File "<<file_path<<" could not be opened in write mode (for logging) "<<endl;
    }
}

void Logger::redirect_output(std::function<void(string)> fun) {
    ((LoggerStreambuf*)rdbuf())->set_redirection_ptr(fun);
    ((LoggerStreambuf*)rdbuf())->use_cout_output(false);
    ((LoggerStreambuf*)rdbuf())->use_fun_output(true);
}

void Logger::use_stdout_output() {
    ((LoggerStreambuf*)rdbuf())->use_cout_output(true);
    ((LoggerStreambuf*)rdbuf())->use_fun_output(false);
}

Logger::~Logger() {
    delete rdbuf();
    if(m_file) {
        m_file.close();
    }
}

void Logger::set_logtype(Log_Type type) {
    write_mut.lock();
    current_prefix=logtype_to_prefix(type);
}

string Logger::logtype_to_prefix(Log_Type type) {
    string prefix="";
    switch (type) {
    case LOG_DEBUG:
        prefix="[DBG] ";
        break;
    case LOG_INFO:
        prefix="[INF] ";
        break;
    case LOG_WARNING:
        prefix="[WAR] ";
        break;
    case LOG_ERROR:
        prefix="[ERR] ";
        break;
    }
    return prefix;
}


