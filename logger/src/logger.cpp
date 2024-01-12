#include <pickle/logger.h>

#include <iostream>

#include <pickle/text_modifier.h>

void pickle::logger::Logger::log(TextModifier modifier, std::initializer_list<std::string> text)
{
    TextModifier defaultModifier(TextColor::FG_DEFAULT);
    std::cout << modifier;
    for (const std::string& textPart : text) {
        std::cout << textPart;
    }
    std::cout << defaultModifier << std::endl;
}