#include <string>
#include <exception>
#include "highriseException.h"

C_HighriseException::C_HighriseException( const char* message )
{
   m_Message = message;
}

C_HighriseException::~C_HighriseException(void)
{
}
