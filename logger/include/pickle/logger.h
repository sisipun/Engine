#ifndef PICKLE_LOGGER
#define PICKLE_LOGGER

#include <string>

namespace pickle
{
    class Logger
    {
    public:
        static void log(const char* text);
    };
}

#endif