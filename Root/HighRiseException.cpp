#include <string>
#include <exception>
#include "HighRiseException.h"

HighriseException::HighriseException(const char* message)
{
    mMessage = message;
}

HighriseException::~HighriseException(void) throw() {}
