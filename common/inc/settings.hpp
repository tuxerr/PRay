#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <string>
#include <map>
#include <tinyxml.h>
#include "logger.hpp"

class Settings {
private:
    Settings(std::string path);         //   << singleton pattern >>
    Settings(Settings const&);          // not implemented
    void operator=(Settings const&);    // not implemented
    static Settings *settings_ptr;      //
    static std::map<std::string,std::string> stringSettings;
    static std::map<std::string,double> doubleSettings;
    static std::map<std::string,float> floatSettings;
    static std::map<std::string,int> intSettings;
    static std::map<std::string,bool> boolSettings;

public:
    static void init(std::string path); //   
    static Settings& getInstance();     //
    static std::string getAsString(std::string name);
    static double getAsDouble(std::string name);
    static float getAsFloat(std::string name);
    static int getAsInt(std::string name);
    static bool getAsBool(std::string name);
};

#endif
