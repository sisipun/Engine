#include <pickle/logger.h>

#include <iostream>

void pickle::Logger::log(std::string text)
{
    std::cout << text << std::endl;
}