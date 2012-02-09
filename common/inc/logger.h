#ifndef DEF_LOGGER
#define DEF_LOGGER

#include <iostream>
#include <functional>
#include <streambuf>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "mutex.h"
#include <signal.h>

#define DEFAULT_LOG_PATH "pray_log.log"

/**
 * \enum Log Types
 * The different log types (used with the write function to affect output).
 */
enum Log_Type {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

//streambuffer class that handles I/O to the logger
class LoggerStreambuf : public std::streambuf
{
private:
    std::string &prefix;
    std::fstream &file;
    Mutex write_mut;

protected:
    static const int bufferSize = 100;   // size of data buffer
    char buffer[bufferSize];            // data buffer
    bool firstflush;

public:
    LoggerStreambuf(std::string &prefix,std::fstream &file);

    virtual ~LoggerStreambuf() { sync(); }

protected:
    int flushBuffer();
    virtual int overflow(int c=EOF);
    virtual int sync();

};

//main logger class
class Logger : public std::ostream
{
public:
    static void init(std::string file_path=DEFAULT_LOG_PATH);
    ~Logger();
    static Logger& log(Log_Type type=LOG_INFO);
    void set_logtype(Log_Type type);

private:
    Logger(std::string file_path);
    Logger(Logger const&);         // Don't Implement.
    void operator=(Logger const&); // Don't implement
    void close();

    std::string logtype_to_prefix(Log_Type type);
    std::string current_prefix;
    std::fstream m_file;

    static Logger *logger_ptr;
    static void (*sigsegv_handlerptr)(int);
    static void sigsegv_newhandler(int sig);
};

#endif
