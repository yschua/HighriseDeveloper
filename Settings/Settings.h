
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

    namespace Settings {

        //extern std::map<std::string, std::string> UserSettings;
        //extern std::map<std::string, std::string> GlobalSettings;
        void Load();
        std::string Get(const std::string& Pref);
        int GetInt(const std::string& Pref);
        int Set(std::string Pref, std::string Value);
        int Set(std::string Pref, std::string Value, bool WriteImmediately);
        void ReadIni(std::string FileName, std::map<std::string, std::string>* Settings);
        void SaveIni(std::string FileName, std::map<std::string, std::string>* Settings);
        //extern bool DocumentLoaded;
        //extern std::string CurSettingsPath;
    }
