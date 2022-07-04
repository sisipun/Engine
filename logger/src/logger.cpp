#include <pickle/logger.h>

#include <iostream>

#include <pickle/text_modifier.h>

void pickle::logger::Logger::log(const char* text)
{
    std::cout << text << std::endl;
}

void pickle::logger::Logger::log(const char* text, TextModifier modifier)
{
    TextModifier defaultModifier(TextColor::FG_DEFAULT);
    std::cout << modifier << text << defaultModifier << std::endl;
}