#include "logger.h"

Logger::Logger() : m_log_type(LOG_INFO) 
{
}

Logger::~Logger() {
    if(m_file) {
        m_file.close();
    }
}

void Logger::init(string file_path) {
    // file is opened in write mode and will be erased if it already exists
    m_file.open(file_path.c_str(),ios::out|ios::trunc);
    if(!m_file) {
        cerr<<"File "<<file_path<<" could not be opened in write mode (for logging) "<<endl;
    }
}

void Logger::close() {
    if(m_file) {
        m_file.close();
    }
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
