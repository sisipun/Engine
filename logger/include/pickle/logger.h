#ifndef PICKLE_LOGGER
#define PICKLE_LOGGER

#include <pickle/text_modifier.h>

#define LOG_WARNING(text) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_YELLOW), text)
#define LOG_ERROR(text) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_RED), text)
#define LOG_INFO(text) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_GREEN), text)
#define LOG_DEBUG(text) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_DEFAULT), text)

namespace pickle
{
    namespace logger
    {
        class Logger
        {
        public:
            static void log(TextModifier modifier, const char *text);
        };
    }
}

#endif