#include <pickle/logger.h>

#include <iostream>

void pickle::Logger::log(const char* text)
{
    std::cout << text << std::endl;
}