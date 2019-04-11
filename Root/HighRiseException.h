#pragma once
#ifndef _HIGHRISEEXCEPTION_H
#define _HIGHRISEEXCEPTION_H

using namespace std;

class HighriseException : public std::exception
{
    std::string mMessage;

public:
    HighriseException(const char* message);
    ~HighriseException(void) throw();

    string& get_Message() { return mMessage; }
};

#endif //_HIGHRISEEXCEPTION_H
