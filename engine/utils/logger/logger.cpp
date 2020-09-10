#include "logger.h"
#include <iostream>

void Logger::log(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
}