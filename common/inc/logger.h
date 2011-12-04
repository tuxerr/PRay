#ifndef DEF_LOGGER
#define DEF_LOGGER

#include <iostream>
#include <string>
#include <fstream>

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


/**
 * \class Newtron's logging class.
 */
class Logger{
public:

    Logger();

    ~Logger();

    void init(string file_path=DEFAULT_LOG_PATH);

    fstream &write(Log_Type type=LOG_INFO);

    void close();

private:
    string logtype_to_prefix(Log_Type type);
    fstream m_file;
    Log_Type m_log_type;
};

#endif
