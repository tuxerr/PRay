#include "logger.h"

LoggerStreambuf::LoggerStreambuf(string &prefix,fstream &file) : 
    prefix(prefix), file(file), firstflush(true) {
    setp (buffer, buffer+(bufferSize-1));
}

int LoggerStreambuf::flushBuffer () {
    int num = pptr()-pbase();
    if(firstflush) {
        write_mut.lock();
        file<<prefix;
        firstflush=false;
    }
    file.write(buffer,num);
    pbump(-num); // reset put pointer accordingly
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
    write_mut.unlock();
    return 0;
}

void Logger::init(string file_path) {
    static Logger log(file_path);
    logger_ptr=&log;
}

Logger& Logger::log() {
    if(logger_ptr!=NULL) {
        return *logger_ptr;
    } else {
        cerr<<"Logger class is not initiated"<<endl;
        exit(0);
    }
}

Logger::Logger(string file_path) : 
    ostream(new LoggerStreambuf(current_prefix,m_file)), ios(0), current_prefix("[INF]")
{
    m_file.open(file_path.c_str(),ios::out|ios::trunc);
    if(!m_file) {
        cerr<<"File "<<file_path<<" could not be opened in write mode (for logging) "<<endl;
    }
}

Logger::~Logger() {
    delete rdbuf();
    if(m_file) {
        m_file.close();
    }
}

void Logger::set_logtype(Log_Type type) {
    current_prefix=logtype_to_prefix(type);
}

string Logger::logtype_to_prefix(Log_Type type) {
    string prefix="";
    switch (type) {
    case LOG_INFO:
        prefix="[INF]";
        break;
    case LOG_WARNING:
        prefix="[WAR]";
        break;
    case LOG_ERROR:
        prefix="[ERR]";
        break;
    }
    return prefix;
}

Logger* Logger::logger_ptr;
