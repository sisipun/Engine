#include <pickle/logger.h>

#include <iostream>

#include <pickle/text_modifier.h>

void pickle::logger::Logger::log(TextModifier modifier, const char* text)
{
    TextModifier defaultModifier(TextColor::FG_DEFAULT);
    std::cout << modifier << text << defaultModifier << std::endl;
}