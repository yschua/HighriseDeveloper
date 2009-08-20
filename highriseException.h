#pragma once
#ifndef _HIGHRISEEXCEPTION_H
#define _HIGHRISEEXCEPTION_H

using namespace std;

class C_HighriseException :
   public std::exception
{
   std::string m_Message;
public:
   C_HighriseException( const char* message );
   ~C_HighriseException(void);

   string& get_Message()
   {
      return m_Message;
   }
};

#endif //_HIGHRISEEXCEPTION_H
