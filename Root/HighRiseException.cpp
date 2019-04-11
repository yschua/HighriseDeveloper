#include "HighRiseException.h"

#include <exception>
#include <string>

HighriseException::HighriseException(const char* message)
{
    mMessage = message;
}

HighriseException::~HighriseException(void) throw() {}
