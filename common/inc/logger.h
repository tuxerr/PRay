#ifndef DEF_LOGGER
#define DEF_LOGGER

#include <iostream>
#include <streambuf>
#include <string>
#include <fstream>
#include "mutex.h"

using namespace std;

#define DEFAULT_LOG_PATH "pray_log.log"

/**
 * \enum Log Types
 * The different log types (used with the write function to affect output).
 */
enum Log_Type {
    LOG_INFO, 
    LOG_WARNING,
    LOG_ERROR
};

//streambuffer class that handles I/O to the logger
class LoggerStreambuf : public streambuf
{
private:
    string &prefix;
    fstream &file;
    Mutex write_mut;

protected:
    static const int bufferSize = 100;   // size of data buffer
    char buffer[bufferSize];            // data buffer
    bool firstflush;

public:
    LoggerStreambuf(string &prefix,fstream &file);
    
    virtual ~LoggerStreambuf() { sync(); }

protected:
    int flushBuffer();
    virtual int overflow(int c=EOF);
    virtual int sync();
    
};

//main logger class
class Logger : public ostream
{
public:
    static void init(string file_path=DEFAULT_LOG_PATH); 
    ~Logger();
    static Logger& log();
    void set_logtype(Log_Type type);

    
private:
    Logger(string file_path);
    Logger(Logger const&);         // Don't Implement.
    void operator=(Logger const&); // Don't implement

    string logtype_to_prefix(Log_Type type);
    string current_prefix;
    fstream m_file;
    static Logger *logger_ptr;

};

#endif
