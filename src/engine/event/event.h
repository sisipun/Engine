#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
    Event(std::string type) : type(type) {}
private:
    std::string type;
};

#endif