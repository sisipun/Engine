#ifndef PICKLE_LOGGER
#define PICKLE_LOGGER

#include <string>
#include <initializer_list>

#include <pickle/text_modifier.h>

#define LOG_WARNING(...) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_YELLOW), {__VA_ARGS__})
#define LOG_ERROR(...) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_RED), {__VA_ARGS__})
#define LOG_INFO(...) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_GREEN), {__VA_ARGS__})
#define LOG_DEBUG(...) pickle::logger::Logger::log(pickle::logger::TextModifier(pickle::logger::TextColor::FG_DEFAULT), {__VA_ARGS__})

namespace pickle
{
    namespace logger
    {
        class Logger
        {
        public:
            static void log(TextModifier modifier, std::initializer_list<std::string> text);
        };
    }
}

#endif