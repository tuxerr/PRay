#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <string>
#include <map>
#include <tinyxml.h>
#include "logger.hpp"

class Settings {
private:
  std::map<std::string,std::string> stringSettings;
  std::map<std::string,double> doubleSettings;
  std::map<std::string,float> floatSettings;
  std::map<std::string,int> intSettings;

public:
  Settings(std::string path);
  std::string getAsString(std::string name);
  double getAsDouble(std::string name);
  float getAsFloat(std::string name);
  int getAsInt(std::string name);
};

#endif
