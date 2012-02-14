#include "settings.hpp"

using namespace std;

Settings* Settings::settings_ptr;
map<string,string> Settings::stringSettings;
map<string,double> Settings::doubleSettings;
map<string,float> Settings::floatSettings;
map<string,int> Settings::intSettings;
map<string,bool> Settings::boolSettings;

void Settings::init(string path) {
    static Settings settings(path);
    settings_ptr = &settings;
}

Settings& Settings::getInstance() {
    return *settings_ptr;
}
        
Settings::Settings(string path) {
    TiXmlDocument doc(path);

    if ( !doc.LoadFile() ) {
        Logger::log(LOG_ERROR) << "Settings loading failed : " << path << endl;
        Logger::log(LOG_ERROR) << "Error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        return ;

    } else {
        Logger::log(LOG_INFO) << "Start loading settings : " << path << endl;

        TiXmlHandle hdl(&doc);
        TiXmlElement* node = hdl.FirstChildElement().FirstChildElement().Element();
        if (node == NULL) {
            Logger::log(LOG_ERROR)<<"Error on top of the file"<<endl;
            return ;
        }

        string nodeName;
        TiXmlAttribute* attribute;
        string attributeName;

        while ( node ) {
            attribute = node->FirstAttribute();
            attributeName = attribute->Name();
            if ( attributeName.compare("s")==0 ) {
                string value;
                node->QueryStringAttribute(attributeName.c_str(), &value);
                stringSettings.insert(pair<string,string>(node->Value(), value));

            } else if ( attributeName.compare("d")==0 ) {
                double value;
                node->QueryDoubleAttribute(attributeName.c_str(), &value);
                doubleSettings.insert(pair<string,double>(node->Value(), value));

            } else if ( attributeName.compare("f")==0 ) {
                float value;
                node->QueryFloatAttribute(attributeName.c_str(), &value);
                floatSettings.insert(pair<string,float>(node->Value(), value));

            } else if ( attributeName.compare("i")==0 ) {
                int value;
                node->QueryIntAttribute(attributeName.c_str(), &value);
                intSettings.insert(pair<string,int>(node->Value(), value));

            } else if ( attributeName.compare("b")==0 ) {
                bool value;
                string s_value;
                node->QueryStringAttribute(attributeName.c_str(), &s_value);
                if ( s_value.compare("true")==0 ) {
                    value = true;
                } else if ( s_value.compare("false")==0 ) {
                    value = false;
                } else {
                    Logger::log(LOG_ERROR)<<"Unknown value of boolean parameter : "<<node->Value()<<endl;
                }
                boolSettings.insert(pair<string,bool>(node->Value(), value));

            } else {
                Logger::log(LOG_ERROR)<<"Unknown type of parameter : "<<node->Value()<<endl;
            }

            node = node->NextSiblingElement();
        }

        Logger::log(LOG_INFO) << "Settings loaded" << endl;
    }
}

string Settings::getAsString(string name) {
    map<string,string>::iterator it = stringSettings.find(name);
    if ( it != stringSettings.end() ) {
        return it->second;
    } else {
        Logger::log(LOG_ERROR)<<"String setting not found : "<<name<<endl;
        return "";
    }
}

double Settings::getAsDouble(string name) {
    map<string,double>::iterator it = doubleSettings.find(name);
    if ( it != doubleSettings.end() ) {
        return it->second;
    } else {
        Logger::log(LOG_ERROR)<<"Double setting not found : "<<name<<endl;
        return 0;
    }
}

float Settings::getAsFloat(string name) {
    map<string,float>::iterator it = floatSettings.find(name);
    if ( it != floatSettings.end() ) {
        return it->second;
    } else {
        Logger::log(LOG_ERROR)<<"Float setting not found : "<<name<<endl;
        return 0;
    }
}

int Settings::getAsInt(string name) {
    map<string,int>::iterator it = intSettings.find(name);
    if ( it != intSettings.end() ) {
        return it->second;
    } else {
        Logger::log(LOG_ERROR)<<"Integer setting not found : "<<name<<endl;
        return 0;
    }
}

bool Settings::getAsBool(string name) {
    map<string,bool>::iterator it = boolSettings.find(name);
    if ( it != boolSettings.end() ) {
        return it->second;
    } else {
        Logger::log(LOG_ERROR)<<"Boolean setting not found : "<<name<<endl;
        return false;
    }
}
