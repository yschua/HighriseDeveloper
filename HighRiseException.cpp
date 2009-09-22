#include <string>
#include <exception>
#include "highriseException.h"

HighriseException::HighriseException( const char* message )
{
   mMessage = message;
}

HighriseException::~HighriseException(void)
throw ()
{
}
