#ifndef PICKLE_LOGGER
#define PICKLE_LOGGER

#include <string>

namespace pickle
{
    class Logger
    {
    public:
        static void log(std::string text);
    };
}

#endif