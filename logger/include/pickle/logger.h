#ifndef PICKLE_LOGGER
#define PICKLE_LOGGER

#include <pickle/text_modifier.h>

#define LOG_WARNING(text) pickle::logger::Logger::log(text, pickle::logger::TextModifier(pickle::logger::TextColor::FG_YELLOW))
#define LOG_ERROR(text) pickle::logger::Logger::log(text, pickle::logger::TextModifier(pickle::logger::TextColor::FG_RED))
#define LOG_INFO(text) pickle::logger::Logger::log(text, pickle::logger::TextModifier(pickle::logger::TextColor::FG_GREEN))
#define LOG_DEBUG(text) pickle::logger::Logger::log(text, pickle::logger::TextModifier(pickle::logger::TextColor::FG_DEFAULT))

namespace pickle
{
    namespace logger
    {
        class Logger
        {
        public:
            static void log(const char *text);

            static void log(const char *text, TextModifier modifier);
        };
    }
}

#endif