#include "Settings.h"

namespace hr {
    namespace Settings {
        bool SettingsAreLoaded = false;
        std::map<std::string, std::string> UserSettings;
        std::map<std::string, std::string> GlobalSettings;
        void Load() {
            ReadIni("Settings.ini", &GlobalSettings);
            SettingsAreLoaded = true;
        }
        std::string Get(const std::string& Pref) {
            if (!SettingsAreLoaded) Load();
            return GlobalSettings[Pref];
        }
        int GetInt(const std::string& Pref) {
            std::string Value = Get(Pref);
            //std::ostringstream StreamValue;
            //StreamValue << Value;
            int IntValue;
            //StreamValue >> IntValue;
            std::stringstream(Value) >> IntValue;
            return IntValue;
        }
        int Set(std::string Pref, std::string Value) {
            return Set(Pref, Value, false);
        }
        int Set(std::string Pref, std::string Value, bool WriteImmediately) {
            UserSettings[Pref] = Value;
            if (WriteImmediately) {
                SaveIni("Settings.ini", &GlobalSettings);
            }
            return 0;
        }
        void SaveIni(std::string FileName, std::map<std::string, std::string>* Settings) {
            std::cout << "Saving settings...\n";

            std::string CurSection;
            std::string FileContents;
            for (
            std::map<std::string, std::string>::const_iterator iter = Settings->begin();
                iter != Settings->end(); ++iter) {
                    std::cout << iter->first << " : " << iter->second << '\n';
                std::string Value = iter->second;
                std::string Section = iter->first;
                unsigned int DotIndex = Section.find('.');
                if (DotIndex == std::string::npos)
                    continue;
                std::string Setting = Section.substr(
                    DotIndex+1, Section.length()-DotIndex-1);

                Section = Section.substr(0, DotIndex);
                //std::cout << "Section: " << Section << '\n';
                //std::cout << "\t" << Setting << " : " << Value << '\n';
                if (CurSection != Section) {
                    FileContents += "\n[" + Section + "]\n";
                    CurSection = Section;
                }
                FileContents += Setting + '=' + Value + '\n';
            }
            //std::cout << FileContents << '\n';
            std::ofstream File (FileName.c_str(), std::ios::trunc);
            if (File.is_open()) {
                File << FileContents;
            } else {
                std::cout << "Unable to write settings to " << FileName << '\n';
            }
        }
        void ReadIni(std::string FileName, std::map<std::string, std::string>* Settings) {
            std::ifstream File (FileName.c_str());
            std::string Line;
            std::string Section;
            if (File.is_open()) {
                while (!File.eof()) {
                    std::getline(File, Line);
                    std::cout << Line;
                    int Offset = 0;
                    while (true) {
                        if (Line[Offset] == ' ' ||
                            Line[Offset] == '\t')
                                Offset++;
                        else
                            break;
                    }
                    if (Line[Offset] == ';')
                        continue;
                    //std::cout << Line;
                    // Remove the trailing \r on linux
                    if (Line[Line.length()-1] == '\r') {
                        Line = Line.substr(0, Line.length()-Offset-1);
                    }

                    if (Line[Offset] == '[' &&
                        Line[Line.length()-1] == ']') {

                            Section = Line.substr(Offset+1, (Line.length()-Offset-2));
                            continue;
                        }
                    unsigned int EqualOffset = Line.find('=');
                    if (EqualOffset == std::string::npos)
                        continue;
                    std::string Setting = Section + '.' +
                        Line.substr(Offset, (EqualOffset-Offset));
                    (*Settings)[Setting] = Line.substr(EqualOffset+1, (Line.length()-EqualOffset));
                    std::cout << Setting << " : " << (*Settings)[Setting] << '\n';
                }
            } else {
                std::cout << "Failed to open file " << FileName << "\n";
            }
        }

        //private:

        //std::string CurSettingsPath = "";
    }
}
